//
// Created by fidel on 2/1/18.
//

#include "spaceClasses.h"
//========================================Start Property definitions==================================================//
Monopoly::Space::Property::Property(
    int SETID,
    int INTRASETID,
    std::string NAME,
    int PROPERTYCOST,
    int HOUSECOST,
    int HOTELCOST,
    int RENT,
    int RENTWITHHOUSE,
    int RENTWITHHOTEL)
    : intrasetID(INTRASETID),
      propertyCost(PROPERTYCOST),
      houseCost(HOUSECOST),
      hotelCost(HOTELCOST),
      rent(RENT),
      rentWithHouse(RENTWITHHOUSE),
      rentWithHotel(RENTWITHHOTEL) {
  type = SpaceType::Property;
  name = NAME;
  ownedBy = nullptr;
  owned = false;
  setID = SETID;
}

void Monopoly::Space::Property::SetOwner(Player *newOwner) {
  this->ownedBy = newOwner;
  this->owned = true;
}

Monopoly::Player *Monopoly::Space::Property::GetOwner() {
  return ownedBy;
}

void Monopoly::Space::Property::ResetOwner() {
  this->owned = false;
  this->ownedBy = nullptr;
}

int Monopoly::Space::Property::GetSetID() {
  return this->setID;
}

int Monopoly::Space::Property::GetCost() const {
  return this->propertyCost;
}

int Monopoly::Space::Property::GetRent() const {
  return this->rent;
}

bool Monopoly::Space::Property::PayRent(Monopoly::Player &loser,
                                        double setMultiplier,
                                        Monopoly::Board &board,
                                        int &rentToReturn) {
  int rent = this->rent;
  Player *setOwner = board.GetSetOwner(this->setID);
  if (setOwner != nullptr && setOwner->GetID() == this->ownedBy->GetID()) {
    rent = static_cast<int>(this->rent * setMultiplier);
  }
  rentToReturn = rent;
  return this->ownedBy->PayPlayer(rent, loser, board);
}

bool Monopoly::Space::Property::IsOwned() const {
  return owned;
}

//============================================Start Go definitions====================================================//

Monopoly::Space::Go::Go(std::string NAME, int SALARY) : salary(SALARY) {
  name = NAME;
  type = SpaceType::Go;
}

int Monopoly::Space::Go::GetSalary() {
  return this->salary;
}
