// Standard headers
#include <stdio.h>

// Internal headers
#include "dimension.h"
#include "direction.h"
#include "position.h"
#include "spy.h"

// Main header
#include "defender.h"

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

struct defender {
  size_t map_width;
  size_t map_height;
  char **map;
};

position_t get_defender_destination(position_t attacker_position, Defender defender_data) {
  position_t destination;
  size_t minimum_distance = __SIZE_MAX__;
  size_t absolute_distance;
  char item;

  for (size_t i = 0; i < defender_data->map_height; i++) {
    item =  defender_data->map[i][defender_data->map_width - 2];
    absolute_distance = attacker_position.i > i ? attacker_position.i - i : i - attacker_position.i;
    
    if (item != 'X' && absolute_distance < minimum_distance) {
      minimum_distance =  absolute_distance;
      destination.i = i;
    }
  }

  destination.j = defender_data->map_width - 2;
  return destination;
}


int is_valid_position(Defender defender_data, int **visited, position_t position) {
  return !visited[position.i][position.j] && defender_data->map[position.i][position.j] != 'X';
}

position_t *get_defender_shortest_path(position_t defender_position, position_t destination, Defender defender_data) {
  position_t position, current_position, next_position, *path;

  path = malloc(defender_data->map_height * defender_data->map_width * sizeof(position_t));

  int directions[8][2] = {DIR_UP, DIR_UP_RIGHT, DIR_RIGHT, DIR_DOWN_RIGHT, DIR_DOWN, DIR_DOWN_LEFT, DIR_LEFT, DIR_UP_LEFT};

  position_t **previous = new_position_matrix(defender_data->map_height, defender_data->map_width, position);
  int **visited = new_int_matrix(defender_data->map_height, defender_data->map_width, 0);

  queue_t queue = new_queue();
  add_element(queue, defender_position);
  previous[defender_position.i][defender_position.j] = defender_position;

  while (!is_empty(queue)) {
    current_position = get_first_element(queue);

    if (equal_positions(current_position, destination)) break;
    
    for (int i = 0; i < 8; i++) {
      next_position.i = current_position.i + directions[i][0];
      next_position.j = current_position.j + directions[i][1];

      if (is_valid_position(defender_data, visited, next_position)) {
        add_element(queue, next_position);
        previous[next_position.i][next_position.j] = current_position;
        visited[next_position.i][next_position.j] = 1;
      }
    }
  }

  path[0] = destination;

  for (size_t i = 1; !equal_positions(path[i-1], defender_position); i++) {
    current_position = path[i - 1];
    path[i] = previous[current_position.i][current_position.j];
  }

  free_matrix(defender_data->map_height, (void **) previous);
  free_matrix(defender_data->map_height, (void **) visited);
  free_queue(queue);
  
  return path;
}

direction_t get_defender_direction(position_t defender_position, position_t destination, Defender defender_data) {
  // position_t current_position;
  position_t *path = get_defender_shortest_path(defender_position, destination, defender_data);

  // current_position = path[0];

  for (size_t i = 1; !equal_positions(path[i-1], defender_position); i++) {
    printf("(%ld, %ld) ", path[i].i, path[i].j);
    fflush(stdout);
  }

  free(path);

  return (direction_t) DIR_LEFT;
}

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
  position_t defender_position, Spy attacker_spy, void* data) {
  
  Defender defender_data = (Defender) data;
  position_t attacker_position = get_spy_position(attacker_spy);
  position_t destination = get_defender_destination(attacker_position, defender_data);
  
  return get_defender_direction(defender_position, destination, defender_data);
}

/*----------------------------------------------------------------------------*/

Defender new_defender(dimension_t dimension, char* map_data) {

  Defender defender = malloc(sizeof(struct defender));

  defender->map_height = dimension.height;
  defender->map_width = dimension.width;
  defender->map = malloc(defender->map_height * sizeof(char*));

  for (size_t i = 0; i < dimension.height; i++) {
    defender->map[i] = malloc(defender->map_width * sizeof(char));

    for (size_t j = 0; j < dimension.width; j++) {
      defender->map[i][j] = map_data[i*dimension.height + j];
    }
  }

  return defender;
}

/*----------------------------------------------------------------------------*/
