//
// Created by mfbut on 1/2/2018.
//

#ifndef HOARDING_MOVE_H
#define HOARDING_MOVE_H
#include "HoardingTypeDefs.h"

Move get_move(const Player* player);
bool is_valid_move();
MoveType move_number_to_move(const int move_number, const Player* player);
void make_move(Move* move, GameState* game_state);
const Player* get_player_to_inspect(const Player* players, const int num_players);
int roll_dice(FILE* rand_file, int num_dice, const int min_dice_roll, const int max_dice_roll);
void move_player(Player* player_to_move, const int num_spaces_to_move, GameState* game_state);
bool passed_go(const Player* player, const Board* board);
bool is_valid_player_id();


#endif //HOARDING_MOVE_H
