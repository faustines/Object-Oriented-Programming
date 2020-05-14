//
// Created by fidel on 2/1/18.
//

#ifndef HOARDINGCPP_PROPERTYHANDLER_H
#define HOARDINGCPP_PROPERTYHANDLER_H
#include <string>
#include <memory>
#include "playerHandler.h"
#include "spaceHandler.h"

namespace Monopoly {
class Space;
class Player;

//=========================================Property declaration=======================================================//
class Space::Property : public Space{
 private:
  int intrasetID;
  int propertyCost;
  int houseCost;
  int hotelCost;
  int rent;
  int rentWithHouse;
  int rentWithHotel;
  //bool owned;
  //Monopoly::Player *ownedBy;

public:
Property(
    int SETID,
    int INTRASETID,
    std::string NAME,
    int PROPERTYCOST,
    int HOUSECOST,
    int HOTELCOST,
    int RENT,
    int RENTWITHHOUSE,
    int RENTWITHHOTEL);

  void SetOwner(Player *newOwner);
  Player *GetOwner();
  bool IsOwned() const;
  void ResetOwner();
  bool PayRent(Monopoly::Player &loser,
                 double setMultiplier,
                 Monopoly::Board &board,
                 int &rentToReturn);
  int GetSetID();
  int GetCost() const;
  int GetRent() const;
};
//===========================================Go declaration===========================================================//
class Space::Go : public Space {
 private:
  int salary;

 public:
  Go(std::string NAME, int SALARY);

  int GetSalary();
};
}


#endif //HOARDINGCPP_PROPERTYHANDLER_H
