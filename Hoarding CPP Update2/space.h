//
// Created by fidel on 1/31/18.
//

#ifndef HOARDINGCPP_SPACEHANDLER_H
#define HOARDINGCPP_SPACEHANDLER_H

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include "rulesHandler.h"

namespace Monopoly {
class Board;
class Player;

enum class SpaceType {
  Go,
  Property,
  Space,
  FreeParking,
  Jail,
  GotoJail,
  PayToBank
};

class Space {
 public:
  class Property;
  class Go;
  class FreeParking;
  class PayToBank;
  class Jail;
  class GotoJail;

 protected:
  std::string name;
  SpaceType type;
  std::vector<Player *> landedOnBy;

 public:
  Space();
  virtual ~Space();
  std::string GetName() const;
  SpaceType GetType();
  virtual void activate(Monopoly::Player &activatingPlayer) = 0;
  virtual void display() const = 0;
  virtual void RemoveLander(Player *player) = 0;
  void AddLander(Player *lander);
};
}

#endif //HOARDINGCPP_SPACEHANDLER_H
