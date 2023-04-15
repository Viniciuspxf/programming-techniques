package br.com.picpay.account_manager.service;

import br.com.picpay.account_manager.exception.InvalidTransactionException;
import br.com.picpay.account_manager.exception.NotFoundException;
import br.com.picpay.account_manager.model.Profile;
import br.com.picpay.account_manager.model.dto.*;
import br.com.picpay.account_manager.repository.ProfileRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.util.concurrent.CompletableFuture;

@Service
public class TransactionService {
    private final MessagesService messagesService;
    private final ProfileRepository profileRepository;
    private final AuthorizationService authorizationService;

    @Autowired
    TransactionService(ProfileRepository profileRepository, AuthorizationService authorizationService,
                       MessagesService messagesService) {
        this.profileRepository = profileRepository;
        this.authorizationService = authorizationService;
        this.messagesService = messagesService;
    }

    @Transactional
    public void makeTransaction(TransactionDTO transaction) {
        Profile payeeProfile = profileRepository.findById(transaction.getPayee())
                .orElseThrow(() ->new NotFoundException("Perfil não encontrado"));

        Profile payerProfile = profileRepository.findById(transaction.getPayer())
                .orElseThrow(() ->new NotFoundException("Perfil não encontrado"));

        if (!payerProfile.isAbleToTransferMoney())
            throw new InvalidTransactionException("Este tipo de usuário não pode transferir dinheiro.");

        if (authorizationService.isAuthorized(transaction)) {
            payerProfile.decreaseAmount(transaction.getValue());
            payeeProfile.increaseAmount(transaction.getValue());
        }
        else throw new InvalidTransactionException("Não autorizado");

        CompletableFuture.runAsync(()-> messagesService.sendTransactionMessage(transaction));
    }
}
