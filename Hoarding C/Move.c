//
// Created by mfbut on 1/2/2018.
//

#include <stdio.h>
#include "Move.h"
#include "GameState.h"
Move get_move(const Player* player) {
  Move player_move;
  int move_number;

  do {
    printf("Player %d please choose an action\n", player->player_name);
    if (player->has_rolled_this_turn) {
      printf("1: End Turn\n");
    } else {
      printf("1: Roll Dice\n");
    }
    printf("2: Inspect Player\n");
    printf("3: Leave Game\n");
    printf("Your action: ");
    scanf("%d", &move_number);
  }while(!is_valid_move());

  player_move.ends_turn = false;
  player_move.type = move_number_to_move(move_number, player);

  return player_move;
}
bool is_valid_move() {
  return true;
}

/**
 * Convert an integer to the corresponding move type
 * @param move_number
 * @param player
 * @return
 */
MoveType move_number_to_move(const int move_number, const Player* player) {
  if(move_number == 1 && player->has_rolled_this_turn){
    return end_turn;
  } else if(move_number == 1 && !player->has_rolled_this_turn){
    return roll;
  } else if(move_number == 2){
    return inspect_player;
  } else if(move_number == 3){
    return leave_game;
  } else{
    printf("In move_number_to_move something terrible happened when converting the move number\n");
    return error_move;
  }
}

/**
 * Make the move on the given game state
 * @param move
 * @param game_state
 */
void make_move(Move* move, GameState* game_state) {

  Player* cur_player = &game_state->players[game_state->player_turn];
  const int move_start_num_players = game_state->num_players;

  if(move->type == end_turn){
    move->ends_turn = true;
  } else if(move->type == roll){
    const int spaces_to_move = roll_dice(game_state->random_numbers_file,
                                         game_state->rules.num_dice_rolled, 1, game_state->rules.max_dice_value);
    printf("You rolled a %d!\n", spaces_to_move);
    move_player(cur_player, spaces_to_move, game_state);
    cur_player->has_rolled_this_turn = true;
    activate_space(&game_state->board.spaces[cur_player->location], cur_player, game_state);

    // if the player went bankrupt during their turn their move is over
    if(game_state->num_players < move_start_num_players){
      move->ends_turn = true;
    } else{
      move->ends_turn = false;
    }

  } else if(move->type == inspect_player){
    const Player* player_to_inspect = get_player_to_inspect(game_state->players, game_state->num_players);
    display_player_info(player_to_inspect);
    move->ends_turn = false;
  } else if(move->type == leave_game){
    go_bankrupt_to_bank(cur_player, game_state);
    remove_player_from_game(cur_player, game_state);
    move->ends_turn = true;
  }



}
int roll_dice(FILE* rand_file, int num_dice, const int min_dice_roll, const int max_dice_roll) {
  int dice_sum = 0;
  int die;
  for (int i = 0; i < num_dice; ++i) {
    fscanf(rand_file, "%d", &die);
    dice_sum += (die % (1 + max_dice_roll - min_dice_roll)) + min_dice_roll;
  }
  return dice_sum;
}

/**
 * Move the specified player the given number of spaces around the board
 * @param player_to_move
 * @param num_spaces_to_move
 * @param game_state
 */
void move_player(Player* player_to_move, const int num_spaces_to_move, GameState* game_state) {
  player_to_move->location += num_spaces_to_move;

  if(passed_go(player_to_move, &game_state->board)){ // if passed go
    const int times_past_go = player_to_move->location / game_state->board.num_spaces;
    player_to_move->cash += game_state->board.spaces[0].property->rent * times_past_go; //go is always at pos 0
    player_to_move->location %= game_state->board.num_spaces;
  }

}

/**
 * Did the player pass go
 * @param player
 * @param board
 * @return
 */
bool passed_go(const Player* player, const Board* board) {
  return player-> location >= board->num_spaces;
}

const Player* get_player_to_inspect(const Player* players, const int num_players) {

  int player_id;
  do{
    printf("Which player would you like to inspect?\n");
    for (int i = 0; i < num_players; ++i) {
      printf("%d for Player %d\n", players[i].player_name, players[i].player_name);
    }
    printf("Your choice: ");
    scanf(" %d", &player_id);
  }while(!is_valid_player_id());

  for (int i = 0; i < num_players; ++i) {
    if(players[i].player_name == player_id){
      return &players[i];
    }
  }

  printf("In get players to inspect.\n"
             "Could not locate Player %d\n", player_id);
  return NULL;

}
bool is_valid_player_id() {
  return true;
}


