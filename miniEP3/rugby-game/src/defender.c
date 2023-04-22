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
    item =  defender_data->map[i][defender_data->map_width - 1];
    absolute_distance = attacker_position.i > i ? attacker_position.i - i : i - attacker_position.i;
    
    if (item != 'X' && absolute_distance < minimum_distance) {
      minimum_distance =  absolute_distance;
      destination.i = i;
    }
  }

  destination.j = defender_data->map_width - 1;

  return destination;
}

/*----------------------------------------------------------------------------*/
/*                              PUBLIC FUNCTIONS                              */
/*----------------------------------------------------------------------------*/

direction_t execute_defender_strategy(
  position_t defender_position, Spy attacker_spy, void* data) {
  
  Defender defender_data = (Defender) data;
  position_t attacker_position = get_spy_position(attacker_spy);
  position_t destination = get_defender_destination(attacker_position, defender_data);
  

  UNUSED(defender_position);
  UNUSED(destination);

  return (direction_t) DIR_LEFT;
}

/*----------------------------------------------------------------------------*/

Defender new_defender(dimension_t dimension, char* map_data) {
  Defender def = malloc(sizeof(struct defender));

  def->map_height = dimension.height;
  def->map_width = dimension.width;
  def->map = malloc(def->map_height * sizeof(char*));

  for (size_t i = 0; i < dimension.height; i++) {
    def->map[i] = malloc(def->map_width * sizeof(char));

    for (size_t j = 0; j < dimension.width; j++) {
      def->map[i][j] = map_data[i*dimension.height + j];
    }
  }

  return def;
}

/*----------------------------------------------------------------------------*/
