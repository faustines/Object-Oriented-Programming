//
// Created by mfbut on 12/30/2017.
//
#include <stdlib.h>
#include "PropertyManager.h"
#include "Utility.h"

/**
 * Create a property manager that represents can hold all of the sets of properties on the given board
 * but has no ownership over any of the properties
 * @param board
 * @return
 */
PropertyManager create_property_manager_from_board(const Board* board) {
  PropertyManager property_manager;
  property_manager.num_property_sets = count_property_sets(board);
  property_manager.property_sets = (PropertySet*) malloc(property_manager.num_property_sets * sizeof(PropertySet));

  // initialize all the sets to be empty
  for (int i = 0; i < property_manager.num_property_sets; ++i) {
    property_manager.property_sets[i] = empty_property_set();
  }

  // figure out the number of properties that are in each set
  for (int i = 0; i < board->num_spaces; ++i) {
    if (board->spaces[i].type == property_space) {
      property_manager.property_sets[board->spaces[i].property->set_id].total_properties_in_set++;
    }
  }

  // now that the number of properties in each set are known make space for the property pointers
  // and initialize them to NULL
  for (int i = 0; i < property_manager.num_property_sets; ++i) {
    PropertySet* curSet = &property_manager.property_sets[i];
    int properties_in_set = curSet->total_properties_in_set;
    curSet->properties = (Propty**)malloc(properties_in_set * sizeof(Propty*));
    for (int j = 0; j < properties_in_set; ++j) {
      curSet->properties[j] = NULL;
    }
  }

  return property_manager;
}


PropertyManager copy_property_manager(const PropertyManager* orig) {
  PropertyManager copy_manager;
  copy_manager.num_property_sets = orig->num_property_sets;
  copy_manager.property_sets = (PropertySet*)malloc(copy_manager.num_property_sets * sizeof(PropertySet));

  for (int i = 0; i < copy_manager.num_property_sets; ++i) {
    copy_manager.property_sets[i] = copy_property_set(&orig->property_sets[i]);
  }

  return copy_manager;
}

void delete_property_manager(PropertyManager* property_manager) {
  for (int i = 0; i < property_manager->num_property_sets; ++i) {
    delete_property_set(&property_manager->property_sets[i]);
  }
  if(property_manager->property_sets != NULL) {
    free(property_manager->property_sets);
  }
  property_manager->num_property_sets = 0;
}

int count_property_sets(const Board* board) {
  int num_sets = 0;
  int* set_numbers = NULL;

  for (int i = 0; i < board->num_spaces; ++i) {
    if (board->spaces[i].type == property_space
        && !is_in_int(board->spaces[i].property->set_id, set_numbers, num_sets)) {
      set_numbers = realloc(set_numbers, (num_sets + 1) * sizeof(int));
      set_numbers[num_sets] = board->spaces[i].property->set_id;
      num_sets++;
    }
  }

  free(set_numbers);
  return num_sets;

  return 0;
}

/**
 *
 * @param property_manager
 */
void display_property_manager(const PropertyManager* property_manager) {
  for (int i = 0; i < property_manager->num_property_sets; ++i) {
    printf("    %d: ", i);
    display_property_set(&property_manager->property_sets[i]);

  }
}

void transfer_properties(PropertyManager* src, PropertyManager* dest, Player* new_owner) {

  for (int i = 0; i < src->num_property_sets; ++i) {
    move_properties_between_sets(&src->property_sets[i], &dest->property_sets[i], new_owner);
  }
}
void take_ownership(PropertyManager* property_manager, Propty* property) {
  own_new_property(&property_manager->property_sets[property->set_id], property);
}
int calculate_owned_property_value(const PropertyManager* property_manager) {
  int value = 0;
  for (int i = 0; i < property_manager->num_property_sets; ++i) {
    value += owned_property_set_value(&property_manager->property_sets[i]);
  }
  return value;
}
void set_owner_property_manager(Player* owner, PropertyManager* property_manager) {
  for (int i = 0; i < property_manager->num_property_sets; ++i) {
    set_owner_property_set(owner, &property_manager->property_sets[i]);
  }
}

