//
// Created by fidel on 1/10/18.
//

#ifndef HOARDING_RULESHANDLER_H
#define HOARDING_RULESHANDLER_H

#include <iostream>
#include <fstream>

namespace Monopoly {

class Rules {
 private:
  int sCash, turnLimit, numPlayers2End, numHousesB4Hotel, maxRerolls;
  double propSetMult, salaryMultLandGo;
  bool mustBuildHousesEvenly, putMoneyInFP, auctionProp;
  std::string temp;
  std::ifstream file;

 public:

  explicit Rules(char *filename);

  void Print();
  int startingCash();
  int numPlayersToEnd();
  int numTurns();
  double setMultiplier();
  double goMultiplier();
  int GetMaxRerolls();
  bool BuildHousesEvenly();
  int GetNumHousesB4Hotel();
  bool AuctionProps();
};
}
#endif //HOARDING_RULESHANDLER_H
