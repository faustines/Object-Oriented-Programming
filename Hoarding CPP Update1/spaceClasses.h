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
  int setID;
  int intrasetID;
  int propertyCost;
  int houseCost;
  int hotelCost;
  int rent;
  int rentWithHouse;
  int rentWithHotel;
  int numHouses;
  int numHotels;
  int numHousesB4Hotels;

public:
Property(int SETID,
         int INTRASETID,
         std::string NAME,
         int PROPERTYCOST,
         int HOUSECOST,
         int HOTELCOST,
         int RENT,
         int RENTWITHHOUSE,
         int RENTWITHHOTEL,
         int HOUSESB4HOTEL);

  void SetOwner(Player *newOwner) override;
  Player *GetOwner() override;
  bool IsOwned() const override;
  void ResetOwner() override;
  bool PayRent(Monopoly::Player &loser,
                 double setMultiplier,
                 Monopoly::Board &board,
                 int &rentToReturn);
  int GetSetID() const override;
  int GetIntrasetID() const override;
  int GetCost() const;
  int GetRent() const;
  int CalcUpgradeCost() const;
  void BuyUpgrade();
  void SellUpgrade();
  int GetNumHouses() const;
  int GetNumHotels() const;
  int GetNumUpgrades() const;
  int GetValUpgrades() const;
  int CalcValDowngrade() const;
  void PrintUpgrades() const;
  void ResetUpgrades();
  int CalcRent(double setMultiplier, Monopoly::Board &board);
  static double expBase2(int exp);
};
//===========================================Go declaration===========================================================//
class Space::Go : public Space {
 private:
  int salary;

 public:
  Go(std::string NAME, int SALARY);
  int GetSetID() const override;
  int GetIntrasetID() const override;
  int GetSalary();
};
}


#endif //HOARDINGCPP_PROPERTYHANDLER_H
