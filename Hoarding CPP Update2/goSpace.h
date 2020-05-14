//
// Created by fidel on 2/23/18.
//

#ifndef HOARDINGCPP_UPDATE2_GOSPACE_H
#define HOARDINGCPP_UPDATE2_GOSPACE_H
#include <string>
#include <memory>
#include "playerHandler.h"
#include "space.h"

namespace Monopoly {
class Space;
class Player;


//===========================================Go declaration===========================================================//
class Space::Go : public Space {
 private:
  int salary;

 public:
  Go(std::string NAME, int SALARY);
  int GetSalary();
  void activate(Monopoly::Player &activatingPlayer) override;
  void display() const override;
  void RemoveLander(Player *player) override;
};
}
#endif //HOARDINGCPP_UPDATE2_GOSPACE_H
