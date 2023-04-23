#include "queue.h"
#include <stdlib.h>

typedef struct node {
    struct node *previous_position;
    struct node *next_position;
    position_t value;
} Node;

struct Queue {
    Node *last_node;
    Node *head_node;
    size_t size;
};

Node *new_node() {
    Node *node = malloc(sizeof(Node));

    node->next_position = NULL;
    node->previous_position = NULL;

    return node;
}

queue_t new_queue() {
    queue_t queue = malloc(sizeof(struct Queue));

    queue->last_node = new_node();
    queue->head_node = queue->last_node;

    queue->size = 0;

    return queue;
}

void add_element(queue_t queue, position_t position) {
    Node * auxiliar_node = queue->head_node->next_position;
    
    Node * new_element = new_node();
    new_element->value = position;
    new_element->next_position = auxiliar_node;
    new_element->previous_position = queue->head_node;

    if (auxiliar_node) {
        auxiliar_node->previous_position = new_element;
    }
    else {
        queue->last_node = new_element;
    }

    queue->size++;
}

position_t get_first_element(queue_t queue) {
    position_t first_element = queue->last_node->value;
    
    Node * auxiliar_node = queue->last_node->previous_position;

    if (auxiliar_node) {
        free(queue->last_node);
        queue->last_node = auxiliar_node;
        queue->last_node->next_position = NULL;
        queue->size--;
    }


    return first_element;
}

int is_empty(queue_t queue) {
    return queue->size == 0;
}

void free_queue(queue_t queue) {
    Node * current_node = queue->head_node;
    Node * next_node;

    while (current_node) {
        next_node = current_node->next_position;
        free(current_node);
        current_node = next_node;
    }

    free(queue);
}
