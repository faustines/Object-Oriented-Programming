
#include "gameStateHandler.h"

void gameLoop(Monopoly::Gamestate &gamestate){
  gamestate.InitGame();
  while(gamestate.gameActive()){
    gamestate.Print();
    int turn = gamestate.UserTurn();
    gamestate.inputExecutor(turn);
  }
  gamestate.Print();
  gamestate.PrintWinners();
}

int main(int argc, char **args) {
  Monopoly::Gamestate gamestate(args);
  gameLoop(gamestate);
  return 0;
}