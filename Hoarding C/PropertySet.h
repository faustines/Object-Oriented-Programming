//
// Created by mfbut on 12/30/2017.
//

#ifndef HOARDING_PROPERTYSET_H
#define HOARDING_PROPERTYSET_H
#include "HoardingTypeDefs.h"
#include "Property.h"



PropertySet empty_property_set();
PropertySet copy_property_set(const PropertySet* orig);
void delete_property_set(PropertySet* property_set);
void display_property_set(const PropertySet* property_set);
void move_properties_between_sets(PropertySet* src, PropertySet* dest, Player* new_owner);
void own_new_property(PropertySet* property_set, Propty* property);
int owned_property_set_value(const PropertySet* property_set);
void set_owner_property_set(Player* owner, PropertySet* property_set);

#endif //HOARDING_PROPERTYSET_H
