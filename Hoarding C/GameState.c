//
// Created by mfbut on 12/29/2017.
//

#include <stdlib.h>
#include "GameState.h"
#include "Utility.h"

GameState setup(char* rules_file_name, char* board_file_name, char* random_nums_file_name) {
  GameState game_state;
  PropertyManager empty_property_manager;

  game_state.rules = read_rules_from_file(rules_file_name);
  game_state.board = read_board_from_file(board_file_name);
  game_state.random_numbers_file = fopen(random_nums_file_name, "r");

  if(game_state.random_numbers_file == NULL){
    printf("Could not open random numbers file %s\n Ending Progarm", random_nums_file_name);
    exit(0);
  }

  empty_property_manager = create_property_manager_from_board(&game_state.board);

  game_state.num_players = get_starting_num_players();
  game_state.players = (Player*) malloc(game_state.num_players * sizeof(Player));
  for (int i = 0; i < game_state.num_players; ++i) {
    game_state.players[i] =
        create_player(i, game_state.rules.starting_cash, copy_property_manager(&empty_property_manager));
  }

  delete_property_manager(&empty_property_manager);

  return game_state;
}
void display_game_state(const GameState* game_state) {
  display_board(game_state);
}
void delete_game_state(GameState* game_state) {

  delete_board(&game_state->board);

  // delete all the players
  for (int i = 0; i < game_state->num_players; ++i) {
    delete_player(&game_state->players[i]);
  }

  if (game_state->players != NULL) {
    free(game_state->players);
  }

  if(game_state->random_numbers_file != NULL){
    fclose(game_state->random_numbers_file);
  }

  game_state->random_numbers_file = NULL;
  game_state->players = NULL;
  game_state->num_players = 0;

}
int get_starting_num_players() {
  int num_players;
  do {
    printf("How many players will be playing: ");
    scanf("%d", &num_players);
  }while(!is_valid_num_players());
  return num_players;
}
bool is_game_over(const GameState* game_state) {
  return game_state->num_players== game_state->rules.num_players_left_to_end_game ||
      (game_state->rules.is_turn_limit && game_state->turn_count == game_state->rules.turn_limit);
}

/**
 * Display the board based on the current game state
 * @param game_state
 */
void display_board(const GameState* game_state) {

  for (int i = 0; i < game_state->board.num_spaces; ++i) {
    printf("%d | ", i);
    display_space(&game_state->board.spaces[i], &game_state->rules, game_state->board.max_space_name_width);
    for (int j = 0; j < game_state->num_players; ++j) {
      if(game_state->players[j].location == i){
        printf("%d ",game_state->players[j].player_name);
      }
    }
    printf("\n");
  }

}
bool is_valid_num_players() {
  return true;
}

/**
 * Remove a player from the game. Should only be called after all of their properties have been
 * given away
 * @param player
 * @param game_state
 */
void remove_player_from_game(Player* player, GameState* game_state) {

  int pos_to_remove = 0;
  for (pos_to_remove = 0; pos_to_remove < game_state->num_players; ++pos_to_remove) {
    if(game_state->players[pos_to_remove].player_name == player->player_name){
      break;
    }
  }

  // remove the player
  delete_player(&game_state->players[pos_to_remove]);
  game_state->num_players--;

  // shuffle over
  for (int i = pos_to_remove; i < game_state->num_players; ++i) {
    game_state->players[i] = game_state->players[i+1];
  }

  // shrink the array to fit
  game_state->players = (Player*)realloc(game_state->players, game_state->num_players * sizeof(Player));

  // this is a cludge to help fix the problem of the player of
  // the next player in line's turn being skipped
  game_state->player_turn--;

  /*
   * update all the owners for the properties
   * This has to be done because when we shifted the properties over
   * The Player pointer in each property is still pointing to the old location in memory
   * which is now the wrong player. So we need to go back through and update all of their owners
   */
  update_player_property_sets(game_state);
}

/**
 * Give all of the player's assests back to the bank
 * @param player
 * @param game_state
 */
void go_bankrupt_to_bank(Player* player, GameState* game_state) {

  for (int i = 0; i < game_state->board.num_spaces; ++i) {
    if(game_state->board.spaces[i].property->owner != NULL &&
        game_state->board.spaces[i].property->owner->player_name == player->player_name){
      game_state->board.spaces[i].property->owner = NULL;
    }
  }

}

/**
 * Change the turn to the next players
 * @param game_state
 */
void change_turn(GameState* game_state) {
  game_state->turn_count++;
  game_state->player_turn = (game_state->player_turn + 1) % game_state->num_players;
  game_state->players[game_state->player_turn].has_rolled_this_turn = false;
}

/**
 * Announce who won the game
 * @param game_state
 */
void declare_winners(const GameState* game_state) {

  int* player_values = (int*)malloc(game_state->num_players * sizeof(int));

  for (int i = 0; i < game_state->num_players; ++i) {
    player_values[i] = get_net_worth(&game_state->players[i]);
  }

  int max_value = max_ar(player_values, game_state->num_players);

  printf("The winners are\n");
  for (int i = 0; i < game_state->num_players; ++i) {
    if(player_values[i] == max_value){
      printf("Player %d\n", game_state->players[i].player_name);
    }
  }


  free(player_values);

}
void update_player_property_sets(GameState* game_state) {
  for (int i = 0; i < game_state->num_players; ++i) {
    set_owned_properties_to_self(&game_state->players[i]);
  }

}

