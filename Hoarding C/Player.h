//
// Created by mfbut on 12/29/2017.
//

#ifndef HOARDING_PLAYER_H
#define HOARDING_PLAYER_H
#include "HoardingTypeDefs.h"
#include "PropertyManager.h"


Player create_player(int player_name, int starting_cash, PropertyManager starting_properties);
void delete_player(Player* player);

void display_player_info(const Player* player);
void give_all(Player* src, Player* dest);

void offer_to_buy(Player* buyer, Propty* property);
bool get_buy_decision(Player* buyer, Propty* property);
bool is_valid_buy_decision();
void purchase_property(Player* buyer, Propty* property);
void pay_rent(Player* payer, Propty* property, GameState* game_state);
int get_net_worth(const Player* player);
void set_owned_properties_to_self(Player* me);


#endif //HOARDING_PLAYER_H
