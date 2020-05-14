//
// Created by mfbut on 12/29/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Rules.h"
#include "Utility.h"
Rules read_rules_from_file(char* file_name) {
  Rules rules;
  FILE* rules_file = fopen(file_name, "r");

  if(rules_file == NULL){
    printf("Failed to open rules file %s\n. Using default rules\n", file_name);
    return get_default_rules();

  }

  rules.num_dice_rolled  = 2;
  rules.max_dice_value = 6;

  fscanf(rules_file, " Starting Cash: %d", &rules.starting_cash);
  fscanf(rules_file, " Turn Limit ( -1 for no turn limit ) : %d", &rules.turn_limit);
  rules.is_turn_limit = rules.turn_limit > -1;
  fscanf(rules_file, " Number of Players Left To End Game: %d", &rules.num_players_left_to_end_game);
  fscanf(rules_file, " Property Set Multiplier: %d", &rules.property_set_multiplier);
  fscanf(rules_file, " Number of Houses Before Hotels: %d", &rules.num_houses_before_hotel);
  fscanf(rules_file, " Must Build Houses Evenly:");
  rules.must_build_evenly = get_yes_no_from_file(rules_file);
  fscanf(rules_file, " Put Money In Free Parking:");
  rules.put_money_in_free_parking = get_yes_no_from_file(rules_file);
  fscanf(rules_file, " Auction Properties:");
  rules.auction_properties = get_yes_no_from_file(rules_file);
  fscanf(rules_file, "Salary Multiplier For Landing On Go: %d", &rules.salary_multiplier_for_landing_on_go);

  fclose(rules_file);

  return rules;
}
Rules get_default_rules() {
  Rules default_rules;
  default_rules.starting_cash = 1500;

  default_rules.num_dice_rolled  = 2;
  default_rules.max_dice_value = 6;


  default_rules.is_turn_limit = false;
  default_rules.turn_limit = -1;

  default_rules.auction_properties = true;
  default_rules.salary_multiplier_for_landing_on_go = 1;
  default_rules.put_money_in_free_parking = false;
  default_rules.must_build_evenly = true;
  default_rules.num_players_left_to_end_game = 1;
  default_rules.property_set_multiplier = 2;
  default_rules.num_houses_before_hotel = 4;

  return default_rules;
}
