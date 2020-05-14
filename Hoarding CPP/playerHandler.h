//
// Created by fidel on 1/31/18.
//

#ifndef HOARDINGCPP_PLAYERHANDLER_H
#define HOARDINGCPP_PLAYERHANDLER_H
#include <string>
#include <exception>
#include <iostream>
#include "boardHandler.h"
namespace Monopoly {
class Board;

class Player {
 private:
  static int numPlayers;
  int monies;
  unsigned int currentPos;
  std::string name;
  int id;
  bool active;

 public:
  bool IsActive() const;
  Player(std::string NAME, int startingCash);
  void TerminatePlayer(Player &winner, Monopoly::Board &board);
  void TerminatePlayer(Board &board);
  bool PayPlayer(int amount, Player &payer, Board &board);
  void PayPlayer(int amount);
  bool TakeMoney(int amount);
  int GetAmountMoney() const;
  std::string GetName() const;
  int GetCurrentPos() const;
  int GetID() const;
  int GetCurrentPosition() const;
  void SetCurrentPosition(int pos);
  void PrintStats() const;
};

}
#endif //HOARDINGCPP_PLAYERHANDLER_H
