//
// Created by fidel on 2/26/18.
//

#ifndef HOARDINGCPP_UPDATE2_JAILSPACE_H
#define HOARDINGCPP_UPDATE2_JAILSPACE_H

#include <string>
#include <iostream>
#include <vector>
#include "space.h"
#include "playerHandler.h"
#include "rulesHandler.h"

namespace Monopoly{
class Space;
class Player;

class Space::Jail : public Space {
 private:
  int turnsInJail;
  int bailAmount;

 public:
  Jail(std::string NAME, int TURNS, int MONEY2LEAVE);
  void activate(Monopoly::Player &activatingPlayer) override;
  void display() const override;
  void RemoveLander(Player *player) override;
  void AddPlayerToJail(Player& criminal);
};

}

#endif //HOARDINGCPP_UPDATE2_JAILSPACE_H
