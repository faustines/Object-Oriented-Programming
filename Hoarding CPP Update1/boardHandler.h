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
#include "spaceHandler.h"
#include "csvHandler.h"
#include "spaceClasses.h"
#include "playerHandler.h"
#include "spaceHandler.h"

namespace Monopoly {
class Player;
class Space;
enum class SpaceType;
class Board {
 private:
  std::ifstream file;
  std::vector<std::shared_ptr<Space>> board;
  int numHousesB4Hotel;

 public:
  explicit Board(char *filename, int housesB4Hotel);
  ~Board();
  void ReadInProp(std::ifstream &file);
  void ReadInGo(std::ifstream &file);
  void Print(std::vector<Player> &players);
  int GetLongestPropName();
  std::vector<int> GetUniqueIDs(bool intraset = false);
  Player *GetSetOwner(int setID) const;
  void ResetDanglingSpaces(const Player &player);
  void TransferProperties(Player &winner, int loserID);
  int NumSpaces() const;
  Monopoly::SpaceType GetType(int num);
  std::shared_ptr<Monopoly::Space::Property> GetProperty(int num) const;
  std::shared_ptr<Monopoly::Space> GetSpace(int num) const;
  std::shared_ptr<Monopoly::Space::Go> GetGo() const;
  void PrintSpaces(int c);
  int GetLongestPlayerName(const std::vector<Player> &players);
  int GetNumDigits(int num);
  std::vector<std::shared_ptr<Space>> GetBoard();
};
}

#endif //HOARDING_BOARDHANDLER_H
