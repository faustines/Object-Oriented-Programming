//
// Created by fidel on 2/26/18.
//

#ifndef HOARDINGCPP_UPDATE2_PAYBANKSPACE_H
#define HOARDINGCPP_UPDATE2_PAYBANKSPACE_H

#include <string>
#include <iostream>
#include "space.h"
#include "playerHandler.h"
#include "rulesHandler.h"

namespace Monopoly{
class Space;
class Player;

class Space::PayToBank : public Space{
 private:
  int amount;

 public:
  static Board *boardSpaces;
  static Rules *rulesList;
  PayToBank(std::string NAME, int AMOUNT);
  void activate(Player& activatingPlayer) override;
  void display() const override;
  void RemoveLander(Player *player) override;
};
}

#endif //HOARDINGCPP_UPDATE2_PAYBANKSPACE_H
