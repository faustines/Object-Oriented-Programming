//
// Created by fidel on 2/25/18.
//

#ifndef HOARDINGCPP_UPDATE2_FREEPARKINGSPACE_H
#define HOARDINGCPP_UPDATE2_FREEPARKINGSPACE_H

#include <string>
#include <iostream>
#include "space.h"
#include "playerHandler.h"
#include "rulesHandler.h"

namespace Monopoly {
class Space;
class Player;

class Space::FreeParking : public Space {
 private:
  static int pool;

 public:
  explicit FreeParking(std::string NAME);
  void activate(Monopoly::Player &activatingPlayer) override;
  void display() const override;
  void RemoveLander(Player *player) override;
  static void AddToPool(int amount);
};
}

#endif //HOARDINGCPP_UPDATE2_FREEPARKINGSPACE_H
