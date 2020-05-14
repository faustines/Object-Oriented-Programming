//
// Created by fidel on 1/31/18.
//

#ifndef HOARDINGCPP_GAMESTATEHANDLER_H
#define HOARDINGCPP_GAMESTATEHANDLER_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include "boardHandler.h"
#include "rulesHandler.h"
#include "diceHandler.h"
#include "inputHandler.h"

namespace Monopoly {
class Gamestate {
 private:
  std::vector<Monopoly::Player> players;
  std::unique_ptr<Monopoly::Board> board;
  std::unique_ptr<Monopoly::Rules> rules;
  std::unique_ptr<Monopoly::DiceRoller> dice;
  int numRollsLeft;
  Player *currentPlayer;
  int currPlayerNum;
  bool playerTerminatedThisTurn;

 public:
  explicit Gamestate (char **args);
  ~Gamestate();
  int CountActivePlayers() const;
  bool gameActive();
  Monopoly::Player *GetNextPlayer();
  void inputExecutor(int userChoice);
  void movePlayer(int roll);
  void landedOnUnownedSpace();
  void landedOnOtherPlayersSpace();
  void InitGame();
  int UserTurn();
  void Print();
  void PrintWinners();
  int getTotalPropValue(const Player &player);
  int getNetWorth(const Player &player);
  int GetHighestNetworth();
};
}

#endif //HOARDINGCPP_GAMESTATEHANDLER_H