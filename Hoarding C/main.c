#include <stdio.h>

// time spent: 1 hour 45 mins

#include "GameState.h"
#include "Move.h"

int main(int argc, char** argv) {
  GameState game_state = setup(argv[1], argv[2], argv[3]);
  Move move;

  while(!is_game_over(&game_state)){
   do{
    display_game_state(&game_state);
    move = get_move(&game_state.players[game_state.player_turn]);
    make_move(&move, &game_state);
    }while(!move.ends_turn);
    change_turn(&game_state);
  }

  display_game_state(&game_state);
  declare_winners(&game_state);
  delete_game_state(&game_state);
  return 0;
}