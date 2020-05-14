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
  bool inJail;
  int turnsInJail;
  int bailAmount;

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
  void PutInJail(int turns, int bail);
  bool InJail() const;
  void DecrementJailtime(Monopoly::Board &board, bool payToParking);
  void LeaveJail();
  bool CanAffordBail() const;
  int GetBailAmount() const;
  int TurnsInJail() const;
  void Deactivate();
};

}
#endif //HOARDINGCPP_PLAYERHANDLER_H
