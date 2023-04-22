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
    item =  attacker_data->map[i][attacker_data->map_width - 1];
    absolute_distance = defender_position.i > i ? defender_position.i - i : i - defender_position.i;
    
    if (item != 'X' && absolute_distance >= maximum_distance) {
      maximum_distance =  absolute_distance;
      destination.i = i;
    }
  }

  destination.j = attacker_data->map_width - 1;

  return destination;
}


/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_attacker_strategy(
    position_t attacker_position, Spy defender_spy, void* data) {
  // TODO: unused parameters, remove these lines later
  UNUSED(attacker_position);
  UNUSED(defender_spy);
  Attacker attacker_data = (Attacker) data;
  UNUSED(attacker_data);

  // TODO: Implement Attacker logic here
  return (direction_t) DIR_RIGHT;
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
