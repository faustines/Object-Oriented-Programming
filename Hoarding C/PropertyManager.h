//
// Created by mfbut on 12/30/2017.
//

#ifndef HOARDING_PROPERTYMANAGER_H
#define HOARDING_PROPERTYMANAGER_H
#include "HoardingTypeDefs.h"
#include "PropertySet.h"
#include "Board.h"

PropertyManager create_property_manager_from_board(const Board* board);
PropertyManager copy_property_manager(const PropertyManager* orig);
void delete_property_manager(PropertyManager* property_manager);
int count_property_sets(const Board* board);
void display_property_manager(const PropertyManager* property_manager);
void transfer_properties(PropertyManager* src, PropertyManager* dest, Player* new_owner);
void take_ownership(PropertyManager* property_manager, Propty* property);
int calculate_owned_property_value(const PropertyManager* property_manager);
void set_owner_property_manager(Player* owner, PropertyManager* property_manager);

#endif //HOARDING_PROPERTYMANAGER_H
