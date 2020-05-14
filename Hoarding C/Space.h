//
// Created by mfbut on 12/30/2017.
//

#ifndef HOARDING_SPACE_H
#define HOARDING_SPACE_H
#include <stdio.h>
#include "HoardingTypeDefs.h"
#include "Property.h"
#include "Rules.h"



Space read_go_space_from_file(FILE* file);
void delete_space(Space* space);
Space read_property_space_from_file(FILE* file);
void display_space(const Space* space, const Rules* rules, const int max_name_width);
void activate_space(Space* space, Player* activating_player, GameState* game_state);
#endif //HOARDING_SPACE_H
