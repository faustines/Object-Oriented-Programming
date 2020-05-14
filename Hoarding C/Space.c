//
// Created by mfbut on 12/30/2017.
//

#include <stdlib.h>
#include "Space.h"
#include "Utility.h"

/**
 * Read a go space in from a file
 * @param file
 * @return
 */
Space read_go_space_from_file(FILE* file) {
  Space go_space;

  go_space.type=go;
  go_space.is_purchasable = false;
  go_space.property = (Propty*) malloc(sizeof(Propty));

  go_space.property->set_id = -1;
  go_space.property->rent = read_int_csv_field(file);
  go_space.property->name = read_str_csv_field(file);
  go_space.property->num_houses_on = 0;
  go_space.property->num_hotels_on = 0;
  go_space.property->is_morgated = false;
  go_space.property->owner = NULL;
  go_space.property->cost_to_purchase = -9;
  go_space.property->cost_to_buy_house = -9;
  go_space.property->cost_to_buy_hotel = -9;

  go_space.property->hotel_rent = 0;
  go_space.property->one_house_rent = 0;
  skip_line(file);
  return go_space;
}

/**
 * Read a property space in from file
 * @param file
 * @return
 */
Space read_property_space_from_file(FILE* file) {
  Space prop_space;
  prop_space.type = property_space;
  prop_space.is_purchasable = true;
  prop_space.property = (Propty*) malloc(sizeof(Propty));

  prop_space.property->set_id = read_int_csv_field(file);
  prop_space.property->intra_set_id = read_int_csv_field(file);
  prop_space.property->name = read_str_csv_field(file);
  prop_space.property->cost_to_purchase = read_int_csv_field(file);
  prop_space.property->cost_to_buy_house = read_int_csv_field(file);
  prop_space.property->cost_to_buy_hotel = read_int_csv_field(file);
  prop_space.property->rent = read_int_csv_field(file);
  prop_space.property->one_house_rent = read_int_csv_field(file);
  prop_space.property->hotel_rent = read_int_csv_field(file);
  prop_space.property->owner = NULL;
  prop_space.property->is_morgated = false;
  prop_space.property->num_houses_on = 0;
  prop_space.property->num_hotels_on = 0;


  return prop_space;
}
void display_space(const Space* space, const Rules* rules, const int max_name_width) {

  printf("%-*s | ", max_name_width, space->property->name);
  for (int i = 0; i < rules->num_houses_before_hotel; ++i) {
    if(i < space->property->num_houses_on){
      printf("h");
    } else if(i < space->property->num_hotels_on){
      printf("H");
    } else{
      printf(" ");
    }
  }

}

/**
 * Deletes a space on the board.
 * Currently this function is the one that releases the property that this space is associated with
 * And so properties shouldn't be deleted elsewhere
 * @param space
 */
void delete_space(Space* space) {
  if(space->property != NULL){
    delete_property(space->property);
  }
  space->property = NULL;
}
void activate_space(Space* space, Player* activating_player, GameState* game_state) {
  if(space->type == go){ // landed_on_go
    // increase salary by multiplier. passing go cash has already been added in when moving the player
    activating_player->cash += space->property->rent * (game_state->rules.salary_multiplier_for_landing_on_go - 1);
  } else if(space->type == property_space){
    if(space->property->owner == activating_player){ // landed on space we own
      return; // do nothing
    } else if(space->property->owner == NULL){
      if(activating_player->cash >= space->property->cost_to_purchase) {
        offer_to_buy(activating_player, space->property);
      } else{
        printf("Player %d you do not have enough money to purchase %s\n"
                   "%s costs $%d, but you only have $%d\n",
               activating_player->player_name, space->property->name,
               space->property->name, space->property->cost_to_purchase, activating_player->cash);
      }
    } else{ // someone else owns this property
      pay_rent(activating_player, space->property, game_state);
    }
  }

}
