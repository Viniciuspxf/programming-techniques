// Standard headers
#include <stdio.h>

// Internal headers
#include "dimension.h"
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "attacker.h"

//malloc
#include <stdlib.h>

//matrix
#include "matrix.h"

//queue
#include "queue.h"

// Macros
#define UNUSED(x) (void)(x) // Auxiliary to avoid error of unused parameter

/*----------------------------------------------------------------------------*/
/*                        PRIVATE STRUCT IMPLEMENTATION                       */
/*----------------------------------------------------------------------------*/

struct attacker {
  size_t map_width;
  size_t map_height;
  char **map;
};


position_t get_attacker_destination(position_t defender_position, Attacker attacker_data) {

  position_t destination;
  size_t maximum_distance = 0;
  size_t absolute_distance;
  char item;

  for (size_t i = 0; i < attacker_data->map_height; i++) {
    item =  attacker_data->map[i][attacker_data->map_width - 2];
    absolute_distance = defender_position.i > i ? defender_position.i - i : i - defender_position.i;
    
    if (item != 'X' && absolute_distance >= maximum_distance) {
      maximum_distance =  absolute_distance;
      destination.i = i;
    }
  }

  destination.j = attacker_data->map_width - 2;

  return destination;
}

int is_attacker_valid_position(Attacker attacker_data, int **visited, position_t position) {
  return !visited[position.i][position.j] && attacker_data->map[position.i][position.j] != 'X';
}

position_t *get_attacker_shortest_path(position_t attacker_position, position_t destination, Attacker attacker_data) {
  position_t position, current_position, next_position, *path;

  path = malloc(attacker_data->map_height * attacker_data->map_width * sizeof(position_t));

  int directions[8][2] = {DIR_UP, DIR_UP_RIGHT, DIR_RIGHT, DIR_DOWN_RIGHT, DIR_DOWN, DIR_DOWN_LEFT, DIR_LEFT, DIR_UP_LEFT};

  position_t **previous = new_position_matrix(attacker_data->map_height, attacker_data->map_width, position);
  int **visited = new_int_matrix(attacker_data->map_height, attacker_data->map_width, 0);

  queue_t queue = new_queue();
  add_element(queue, attacker_position);
  previous[attacker_position.i][attacker_position.j] = attacker_position;

  while (!is_empty(queue)) {
    current_position = get_first_element(queue);

    if (equal_positions(current_position, destination)) break;
    
    for (int i = 0; i < 8; i++) {
      next_position.i = current_position.i + directions[i][0];
      next_position.j = current_position.j + directions[i][1];

      if (is_attacker_valid_position(attacker_data, visited, next_position)) {
        add_element(queue, next_position);
        previous[next_position.i][next_position.j] = current_position;
        visited[next_position.i][next_position.j] = 1;
      }
    }
  }

  path[0] = destination;

  for (size_t i = 1; !equal_positions(path[i-1], attacker_position); i++) {
    current_position = path[i - 1];
    path[i] = previous[current_position.i][current_position.j];
  }

  free_matrix(attacker_data->map_height, (void **) previous);
  free_matrix(attacker_data->map_height, (void **) visited);
  free_queue(queue);
  
  return path;
}

direction_t get_attacker_direction(position_t attacker_position, position_t destination, Attacker attacker_data) {
  position_t current_position, next_position;
  position_t *path = get_attacker_shortest_path(attacker_position, destination, attacker_data);
  direction_t direction;

  size_t i;
  int path_size = 0;

  for (i = 1; !equal_positions(path[i-1], attacker_position); i++) {
    path_size++;
  }

  if (!path_size) {
    direction = (direction_t) DIR_STAY;
  }
  else {
    current_position = path[i-1];
    next_position = path[i-2];
    direction =  (direction_t) {next_position.i - current_position.i, next_position.j - current_position.j};
  }

  free(path);

  return direction;
}


/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
  position_t attacker_position, Spy defender_spy, void* data) {
  
  Attacker attacker_data = (Attacker) data;
  position_t defender_position = get_spy_position(defender_spy);
  position_t destination = get_attacker_destination(defender_position, attacker_data);
  
  return get_attacker_direction(attacker_position, destination, attacker_data);
}

/*----------------------------------------------------------------------------*/

Attacker new_attacker(dimension_t dimension, char* map_data){
  Attacker atac = malloc(sizeof(struct attacker));

  atac->map_height = dimension.height;
  atac->map_width = dimension.width;
  atac->map = malloc(atac->map_height * sizeof(char*));

  for (size_t i = 0; i < dimension.height; i++) {
    atac->map[i] = malloc(atac->map_width * sizeof(char));
    
    for (size_t j = 0; j < dimension.width; j++) {
      atac->map[i][j] = map_data[i*dimension.height + j];
    }
  }

  return atac;
}

/*----------------------------------------------------------------------------*/
