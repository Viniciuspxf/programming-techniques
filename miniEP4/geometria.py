from abc import ABC
from abc import abstractmethod
import math


class FormaGeometrica(ABC):
    def __init__(self, simbolo: str):
        self.simbolo = simbolo

    def imprime(self):
        print(f"Forma geometrica {self.simbolo} {self.calculaArea()}")

    @abstractmethod
    def calculaArea(self):
        pass


class Quadrado(FormaGeometrica):
    def __init__(self, lado: float):
        super().__init__('q')
        self.lado = lado

    def calculaArea(self):
        return self.lado * self.lado


class Retangulo(FormaGeometrica):
    def __init__(self, altura: float, largura: float):
        super().__init__('r')
        self.altura = altura
        self.largura = largura

    def calculaArea(self):
        return self.altura * self.largura


class Circulo(FormaGeometrica):
    def __init__(self, raio: float):
        super().__init__('c')
        self.raio = raio

    def calculaArea(self):
        return math.pi * self.raio * self.raio
    
class Triangulo(FormaGeometrica):
    def __init__(self, base: float, altura: float):
        super().__init__('t')
        self.base = base
        self.altura = altura

    def calculaArea(self):
        return self.base * self.altura / 2

if __name__ == "__main__":
    q = Quadrado(5.0)
    q.imprime()
    # Quadrado.imprime(q)

    r = Retangulo(4.0, 3.0)
    r.imprime()

    c = Circulo(1.0)
    c.imprime()

    t = Triangulo(3.0, 4.0)
    t.imprime()
