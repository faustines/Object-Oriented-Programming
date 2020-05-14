//
// Created by mfbut on 12/29/2017.
//

#include <ctype.h>
#include "Player.h"
#include "GameState.h"

Player create_player(int player_name, int starting_cash, PropertyManager starting_properties) {
  Player new_player;
  new_player.player_name = player_name;
  new_player.cash = starting_cash;
  new_player.location = 0; // start at beginning space
  new_player.has_rolled_this_turn = false;
  new_player.property_manager = starting_properties;
  return new_player;
}

/**
 * Delete a player
 * @param player
 */
void delete_player(Player* player) {
  player->cash = 0;
  player->player_name = -9;
  player->location = -9;
  delete_property_manager(&player->property_manager);
}

/**
 * Display detailed information about this player
 * @param player
 */
void display_player_info(const Player* player) {

  if(player == NULL){
    return;
  }

  printf("Player %d\n", player->player_name);
  printf("  Cash: $%d\n", player->cash);
  printf("  Properties owned\n");
  display_property_manager(&player->property_manager);
}

/**
 * Give all the material possessions from src to dest
 * @param src
 * @param dest
 */
void give_all(Player* src, Player* dest) {

  // give all cash
  dest->cash += src->cash;
  src->cash = 0;

  transfer_properties(&src->property_manager, &dest->property_manager, dest);

}

void offer_to_buy(Player* buyer, Propty* property) {

  bool to_buy = get_buy_decision(buyer, property);

  if(to_buy){
    purchase_property(buyer, property);
  }
}


bool get_buy_decision(Player* buyer, Propty* property) {
  char user_in;
  do{
    printf("Player %d would you like to buy %s for $%d?\n"
               "The rent on this property is $%d\n"
               "You currently have $%d\n"
               "Y for yes, N for no: ",
           buyer->player_name, property->name, property->cost_to_purchase, property->rent, buyer->cash);
    scanf(" %c", &user_in);
  }while(!is_valid_buy_decision());
  return tolower(user_in) == 'y';
}


bool is_valid_buy_decision() {
  return true;
}

void purchase_property(Player* buyer, Propty* property) {
  buyer->cash -= property->cost_to_purchase;
  property->owner = buyer;
  take_ownership(&buyer->property_manager, property);
}
void pay_rent(Player* payer, Propty* property, GameState* game_state) {

  bool has_monopoly = property->owner->property_manager.property_sets[property->set_id].num_properties_owned ==
      property->owner->property_manager.property_sets[property->set_id].total_properties_in_set;
  const int rent_cost = has_monopoly ? property->rent * game_state->rules.property_set_multiplier: property->rent;

  if(rent_cost > payer->cash){
    printf("Player %d went bankrupt to Player %d\n", payer->player_name, property->owner->player_name);
    give_all(payer, property->owner);
    remove_player_from_game(payer, game_state);
  } else{
    payer->cash -= rent_cost;
    property->owner->cash += rent_cost;
    printf("Player %d payed Player %d $%d for landing on %s\n", payer->player_name, property->owner->player_name,
           rent_cost, property->name);
  }

}

/**
 * Figure out the how much this player is worth
 * @param player
 * @return
 */
int get_net_worth(const Player* player) {

  return player->cash + calculate_owned_property_value(&player->property_manager);
}
void set_owned_properties_to_self(Player* me) {
  set_owner_property_manager(me, &me->property_manager);
}
