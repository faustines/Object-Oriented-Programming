//
// Created by mfbut on 12/29/2017.
//

#ifndef HOARDING_GAMESTATE_H
#define HOARDING_GAMESTATE_H

#include <stdbool.h>
#include "HoardingTypeDefs.h"
#include "Player.h"
#include "Board.h"
#include "Rules.h"



GameState setup(char* rules_file_name, char* board_file_name, char* random_nums_file_name);
void delete_game_state(GameState* game_state);
void display_game_state(const GameState* game_state);
int get_starting_num_players();
bool is_game_over(const GameState* game_state);
void display_board(const GameState* game_state);
bool is_valid_num_players();
void remove_player_from_game(Player* player, GameState* game_state);
void go_bankrupt_to_bank(Player* player, GameState* game_state);
void change_turn(GameState* game_state);
void declare_winners(const GameState* game_state);
void update_player_property_sets(GameState* game_state);

#endif //HOARDING_GAMESTATE_H
