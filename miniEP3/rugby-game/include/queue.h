#include "position.h"

typedef struct Queue *queue_t;

queue_t new_queue();

void add_element(queue_t queue, position_t position);

position_t get_first_element(queue_t queue);

int is_empty(queue_t queue);

void free_queue(queue_t queue);