//
// Created by fidel on 1/10/18.
//

#ifndef HOARDING_RULESHANDLER_H
#define HOARDING_RULESHANDLER_H

#include <iostream>
#include <cctype>
#include <fstream>

namespace Monopoly {

class Rules {
 private:
  int sCash, turnLimit, numPlayers2End, numHousesB4Hotel;
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
};
}
#endif //HOARDING_RULESHANDLER_H
