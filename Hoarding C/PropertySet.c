//
// Created by mfbut on 12/30/2017.
//

#include <stdlib.h>
#include "PropertySet.h"

/**
 * Create a new empty Property Set
 * @param property_set
 */
PropertySet empty_property_set() {
  PropertySet new_property_set;
  new_property_set.total_properties_in_set = 0;
  new_property_set.num_properties_owned = 0;
  new_property_set.properties = NULL;
  return new_property_set;
}

/**
 * make a copy of the property set given
 * @param orig
 * @return
 */
PropertySet copy_property_set(const PropertySet* orig) {
  PropertySet copy;
  copy.total_properties_in_set = orig->total_properties_in_set;
  copy.num_properties_owned = orig->num_properties_owned;

  copy.properties = (Propty**) malloc(orig->total_properties_in_set * sizeof(Propty*));
  for (int i = 0; i < orig->total_properties_in_set; ++i) {
    copy.properties[i] = orig->properties[i];
  }

  return copy;
}

/**
 * Delete the specified property_set
 * @param property_set
 */
void delete_property_set(PropertySet* property_set) {
  if(property_set->properties != NULL){
    free(property_set->properties);
  }
  property_set->total_properties_in_set = 0;
  property_set->num_properties_owned = 0;
}
void display_property_set(const PropertySet* property_set) {
  int num_property_printed = 0;
  for (int i = 0; i < property_set->total_properties_in_set; ++i) {
    if(property_set->properties[i] != NULL){
      printf("%s", property_set->properties[i]->name);
      num_property_printed++;
      if(i < property_set->total_properties_in_set - 1 && num_property_printed < property_set->num_properties_owned){
        printf(" | ");
      }
    }
  }
  printf("\n");
}

/**
 * Move all the properties held in src to dest
 * @param src
 * @param dest
 */
void move_properties_between_sets(PropertySet* src, PropertySet* dest, Player* new_owner) {
  for (int i = 0; i < src->total_properties_in_set; ++i) {
    if(src->properties[i] != NULL){
      // give property to dest
      dest->properties[i] = src->properties[i];
      dest->properties[i]->owner = new_owner;
      dest->num_properties_owned++;
      // src no longer has the property
      src->properties[i] = NULL;
      src->num_properties_owned--;
    }
  }
}
void own_new_property(PropertySet* property_set, Propty* property) {
  property_set->properties[property->intra_set_id] = property;
  property_set->num_properties_owned++;
}
int owned_property_set_value(const PropertySet* property_set) {
  int value = 0;
  for (int i = 0; i < property_set->total_properties_in_set; ++i) {
    if(property_set->properties[i] != NULL){
      value +=  property_set->properties[i]->cost_to_purchase +
          property_set->properties[i]->num_houses_on * property_set->properties[i]->cost_to_buy_house +
          property_set->properties[i]->num_hotels_on * property_set->properties[i]->cost_to_buy_hotel;
    }
  }
  return value;
}

void set_owner_property_set(Player* owner, PropertySet* property_set) {
  for (int i = 0; i < property_set->total_properties_in_set; ++i) {
    if(property_set->properties[i] != NULL){
      property_set->properties[i]->owner = owner;
    }
  }
}
