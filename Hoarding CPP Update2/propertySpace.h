//
// Created by fidel on 2/23/18.
//

#ifndef HOARDINGCPP_UPDATE2_PROPERTY_H
#define HOARDINGCPP_UPDATE2_PROPERTY_H
#include <string>
#include <memory>
#include <vector>
#include "playerHandler.h"
#include "space.h"
#include "rulesHandler.h"

namespace Monopoly {
class Space;
class Player;
//=========================================Property declaration=======================================================//
class Space::Property : public Space {
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
  bool owned;
  Player *ownedBy;

 public:
  static Board *boardSpaces;
  static std::vector<Player> *playerRoster;
  static Rules *rulesList;
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

  void SetOwner(Player *newOwner);
  Player *GetOwner();
  bool IsOwned() const;
  void ResetOwner();
  bool PayRent(Monopoly::Player &loser,
               double setMultiplier,
               Monopoly::Board &board,
               int &rentToReturn);
  int GetSetID() const;
  int GetIntrasetID() const;
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
  int PrintUpgrades() const;
  void ResetUpgrades();
  int CalcRent(double setMultiplier, Player *setOwner);
  void activate(Monopoly::Player &activatingPlayer) override;
  static double expBase2(int exp);
  void landedOnOtherPlayersSpace(Player *player, double setMultiplier, Board *board);
  void landedOnUnownedSpace(std::vector<Player> &players,
                              Player *player,
                              bool auction,
                              Player &activatingPlayer);
  Monopoly::Player *DoAuction(std::vector<Player> &players, int &price, Player &startingPlayer);
  static Monopoly::Player *GetNextAuctionPlayer(std::vector<Monopoly::Player> &auctionPlayers,int &startingPlayer);
  void display() const override;
  void RemoveLander(Player *player) override;
  Player *GetFirstActivePlayer(int &index, std::vector<Player> &vect2Search);
};
}
#endif //HOARDINGCPP_UPDATE2_PROPERTY_H
