//
// Created by fidel on 1/9/18.
//

#ifndef HOARDING_BOARDHANDLER_H
#define HOARDING_BOARDHANDLER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <map>
#include <memory>
#include <sstream>
#include <algorithm>
#include "space.h"
#include "csvHandler.h"
#include "playerHandler.h"
#include "space.h"
#include "inputHandler.h"
#include "propertySpace.h"
#include "goSpace.h"
#include "freeparkingSpace.h"
#include "paybankSpace.h"
#include "jailSpace.h"
#include "gotojailSpace.h"

namespace Monopoly {
class Player;
class Space;
enum class SpaceType;
class Board {
 private:
  std::ifstream file;
  std::vector<std::unique_ptr<Space>> board;
  std::vector<Space::Property *> properties;
  int numHousesB4Hotel;

 public:
  static int maxPropName;
  static int maxPlayerName;
  explicit Board(char *filename, int housesB4Hotel);
  ~Board();
  void ReadInProp(std::ifstream &file);
  void ReadInGo(std::ifstream &file);
  void ReadInFP(std::ifstream &file);
  void ReadInPay(std::ifstream &file);
  void ReadInJail(std::ifstream &file);
  void ReadInGotoJail(std::ifstream &file);
  void Print(std::vector<Player> &players);
  int GetLongestSpaceName();
  std::vector<int> GetUniqueIDs(bool intraset = false);
  Player *GetSetOwner(int setID) const;
  void ResetDanglingSpaces(const Player &player);
  void TransferProperties(Player &winner, int loserID);
  int NumSpaces() const;
  int NumProps() const;
  Monopoly::SpaceType GetType(int num);
  int GetLongestPlayerName(const std::vector<Player> &players);
  int GetNumDigits(int num);
  Monopoly::Space *At(int num);
  Space::Property *GetProperty(int num);
  Space::Go *GetGo();
  std::vector<Monopoly::Space::Property *> GetUpgradableProps(Player &player2Check,
                                                              bool buildEvenly,
                                                              bool downgradeOverride = false);
  std::vector<Monopoly::Space::Property *> GetDowngradeableProps(Player &player2Check, bool buildEvenly);
  void SellToSurvive(Player &loser, int owed);
  void RemoveLander(Player *p2r);
};
}

#endif //HOARDING_BOARDHANDLER_H
