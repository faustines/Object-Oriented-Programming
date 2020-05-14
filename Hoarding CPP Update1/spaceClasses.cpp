//
// Created by fidel on 2/1/18.
//

#include "spaceClasses.h"
//========================================Start Property definitions==================================================//
Monopoly::Space::Property::Property(int SETID,
                                    int INTRASETID,
                                    std::string NAME,
                                    int PROPERTYCOST,
                                    int HOUSECOST,
                                    int HOTELCOST,
                                    int RENT,
                                    int RENTWITHHOUSE,
                                    int RENTWITHHOTEL,
                                    int HOUSESB4HOTEL)
    : intrasetID(INTRASETID),
      propertyCost(PROPERTYCOST),
      houseCost(HOUSECOST),
      hotelCost(HOTELCOST),
      rent(RENT),
      rentWithHouse(RENTWITHHOUSE),
      rentWithHotel(RENTWITHHOTEL),
      numHousesB4Hotels(HOUSESB4HOTEL){
  type = SpaceType::Property;
  name = NAME;
  ownedBy = nullptr;
  owned = false;
  setID = SETID;
  numHouses = 0;
  numHotels = 0;
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
  ResetUpgrades();
}

int Monopoly::Space::Property::GetCost() const {
  return this->propertyCost;
}

int Monopoly::Space::Property::GetRent() const {
  return this->rent;
}

int Monopoly::Space::Property::GetSetID() const {
  return setID;
}

int Monopoly::Space::Property::GetIntrasetID() const {
  return intrasetID;
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
  if(numHouses > 0) rent = rentWithHouse*expBase2(numHouses - 1);
  if(numHotels > 0) rent = rentWithHotel;
  rentToReturn = rent;
  return this->ownedBy->PayPlayer(rent, loser, board);
}

bool Monopoly::Space::Property::IsOwned() const {
  return owned;
}

int Monopoly::Space::Property::GetValUpgrades() const {
  if (numHotels == 0){
    return (numHouses * houseCost);
  } else {
    return (numHotels * hotelCost + numHousesB4Hotels * houseCost);
  }
}

int Monopoly::Space::Property::GetNumHouses() const {
  return numHouses;
}

int Monopoly::Space::Property::CalcUpgradeCost() const {
  if(numHouses == numHousesB4Hotels){
    return hotelCost;
  } else {
    return houseCost;
  }
}

void Monopoly::Space::Property::BuyUpgrade() {
  ownedBy->TakeMoney(CalcUpgradeCost());
  numHouses++;
  if(numHouses > numHousesB4Hotels){
    numHouses = 0;
    numHotels++;
  }
}

int Monopoly::Space::Property::CalcValDowngrade() const {
  if(numHouses == 0 && numHotels == 0){
    return 0;
  } else if(numHouses == 0 && numHotels > 0) {
    return hotelCost / 2;
  } else {
    return houseCost / 2;
  }
}

void Monopoly::Space::Property::SellUpgrade() {
  if(numHouses == 0 && numHotels > 0) {
    ownedBy->PayPlayer(hotelCost / 2);
    numHotels--;
    numHouses = numHousesB4Hotels;
  } else {
    ownedBy->PayPlayer(houseCost / 2);
    numHouses--;
  }
}

void Monopoly::Space::Property::PrintUpgrades() const {
  for (int i = 0; i < numHotels; i++){
    std::cout << "H";
  }
  for (int i = 0; i < numHouses; i++){
    std::cout << "h";
  }
}

int Monopoly::Space::Property::GetNumUpgrades() const {
  if(numHotels > 0){
    return (numHotels * numHousesB4Hotels) + 1;
  }
  else {
    return numHouses;
  }

}

void Monopoly::Space::Property::ResetUpgrades() {
  numHotels = 0;
  numHouses = 0;
}

int Monopoly::Space::Property::GetNumHotels() const {
  return numHotels;
}

int Monopoly::Space::Property::CalcRent(double setMultiplier, Monopoly::Board &board) {
  int rent = this->rent;
  Player *setOwner = board.GetSetOwner(this->setID);
  if (setOwner != nullptr && setOwner->GetID() == this->ownedBy->GetID()) {
    rent = static_cast<int>(this->rent * setMultiplier);
  }
  if(numHouses > 0) rent = rentWithHouse*expBase2(numHouses - 1);
  if(numHotels > 0) rent = rentWithHotel;
  return rent;
}

double Monopoly::Space::Property::expBase2(int exp) {
  return (1 << exp);
}

//============================================Start Go definitions====================================================//

Monopoly::Space::Go::Go(std::string NAME, int SALARY) : salary(SALARY) {
  name = NAME;
  type = SpaceType::Go;
}

int Monopoly::Space::Go::GetSalary() {
  return this->salary;
}

int Monopoly::Space::Go::GetSetID() const {
  return -1;
}

int Monopoly::Space::Go::GetIntrasetID() const {
  return -1;
}
