//
// Created by fidel on 1/31/18.
//

#ifndef HOARDINGCPP_GAMESTATEHANDLER_H
#define HOARDINGCPP_GAMESTATEHANDLER_H
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
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
  int numTurnsLeft;
  int numRollsThisTurn;
  Player *currentPlayer;
  int currPlayerNum;
  bool playerTerminatedThisTurn;
  bool rolledDoubles;

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
  void SellToSurvive(Player &loser, int owed);
  std::vector<Monopoly::Space *> GetUpgradableProps(Player &player2Check,
                                                      bool buildEvenly,
                                                      bool downgradeOverride = false);
  std::vector<Monopoly::Space *> GetDowngradeableProps(Player &player2Check, bool buildEvenly);
  Player * DoAuction(const Space::Property &aucprop, int &price, Player *startingPlayer);
  Monopoly::Player *GetNextAuctionPlayer(std::vector<Monopoly::Player> &auctionPlayers,int &startingPlayer);
};
}

#endif //HOARDINGCPP_GAMESTATEHANDLER_H