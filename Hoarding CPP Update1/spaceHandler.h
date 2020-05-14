//
// Created by fidel on 1/31/18.
//

#ifndef HOARDINGCPP_SPACEHANDLER_H
#define HOARDINGCPP_SPACEHANDLER_H

#include <string>
#include <memory>
#include <iostream>

namespace Monopoly {
class Board;
class Player;

enum class SpaceType {
  Go,
  Property,
  Space
};

class Space {
 public:
  class Property;
  class Go;

 protected:
  std::string name;
  SpaceType type;
  bool owned;
  Monopoly::Player *ownedBy;

 public:
  Space();
  virtual ~Space();
  std::string GetName() const;
  SpaceType GetType();
  virtual void Activate();
  virtual Player *GetOwner();
  virtual bool IsOwned() const;
  virtual void ResetOwner();
  virtual void SetOwner(Player *newOwner);
  virtual int GetSetID() const = 0;
  virtual int GetIntrasetID() const = 0;
};
}

#endif //HOARDINGCPP_SPACEHANDLER_H
