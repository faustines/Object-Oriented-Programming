//
// Created by fidel on 2/26/18.
//

#ifndef HOARDINGCPP_UPDATE2_GOTOJAILSPACE_H
#define HOARDINGCPP_UPDATE2_GOTOJAILSPACE_H

#include <string>
#include <iostream>
#include <vector>
#include "space.h"
#include "playerHandler.h"
#include "rulesHandler.h"

namespace Monopoly{
class Space;
class Player;

class Space::GotoJail : public Space {
 private:
  int index;

 public:
  static Board *boardSpaces;
  GotoJail(std::string NAME, int INDEX);
  void activate(Monopoly::Player &activatingPlayer) override;
  void display() const override;
  void RemoveLander(Player *player) override;
};

}

#endif //HOARDINGCPP_UPDATE2_GOTOJAILSPACE_H
