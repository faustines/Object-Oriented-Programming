//
// Created by fidel on 2/23/18.
//

#include "propertySpace.h"
#include "gameStateHandler.h"

Monopoly::Rules *Monopoly::Space::Property::rulesList = nullptr;
Monopoly::Board *Monopoly::Space::Property::boardSpaces = nullptr;
std::vector<Monopoly::Player> *Monopoly::Space::Property::playerRoster = nullptr;

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

int Monopoly::Space::Property::PrintUpgrades() const {
  int count = 0;
  for (int i = 0; i < numHotels; i++){
    count++;
    std::cout << "H";
  }
  for (int i = 0; i < numHouses; i++){
    count++;
    std::cout << "h";
  }
  return count;
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

int Monopoly::Space::Property::CalcRent(double setMultiplier, Player *setOwner) {
  int rent = this->rent;
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

void Monopoly::Space::Property::activate(Monopoly::Player &activatingPlayer) {
  AddLander(&activatingPlayer);
  std::sort(landedOnBy.begin(), landedOnBy.end(), // Sort players by ID with lambda
            [](const Player *a, const Player *b) -> bool { return a->GetID() < b->GetID(); });
  if (owned && ownedBy->GetID() != activatingPlayer.GetID()) {
    landedOnOtherPlayersSpace(&activatingPlayer, rulesList->setMultiplier(), boardSpaces);
  } else if (!owned) {
    landedOnUnownedSpace(*playerRoster, &activatingPlayer, rulesList->AuctionProps(), activatingPlayer);
  } else if (owned && ownedBy->GetID() == activatingPlayer.GetID()) {
    std::cout << activatingPlayer.GetName() << ", you landed on " << name << " which you already own\n";
  }
}
void Monopoly::Space::Property::landedOnOtherPlayersSpace(Player *player, double setMultiplier, Board *board) {
  int rent = CalcRent(setMultiplier, board->GetSetOwner(setID));
  if (rent > player->GetAmountMoney()) {
    board->SellToSurvive(*player, rent);
  }
  if (PayRent(*player,
              setMultiplier,
              *board,
              rent)) {
    std::cout << player->GetName() << " paid " << ownedBy->GetName() << " $" << rent
              << " for landing on " << name << std::endl;
  } else {
    player->TerminatePlayer(*ownedBy, *board);
  }
}

void Monopoly::Space::Property::landedOnUnownedSpace(std::vector<Player> &players,
                                                     Player *player,
                                                     bool auction,
                                                     Player &activatingPlayer) {
  int winningPrice = 0;
  if (!owned && player->GetAmountMoney() >= propertyCost) {
    //Property is unowned and player has enough money to buy
    if (Monopoly::offerBuy(*player, *this)) {
      SetOwner(player);
      player->TakeMoney(propertyCost);
      std::cout << player->GetName() << " bought "
                << name << " for $"
                << propertyCost << std::endl;
    } else if (auction) {
      Player *winner = DoAuction(players, winningPrice, activatingPlayer);
      if (winner != nullptr) {
        winner->TakeMoney(winningPrice);
        SetOwner(winner);
      }
    }
  } else if (!owned && player->GetAmountMoney() < propertyCost) {
    std::cout << player->GetName() << ", you don't have enough money to afford "
              << name << ".\n";
    std::cout << name << " costs $"
              << propertyCost << " but you only have $"
              << player->GetAmountMoney() << std::endl;
  }
}

Monopoly::Player *Monopoly::Space::Property::GetNextAuctionPlayer(std::vector<Monopoly::Player> &auctionPlayers,
                                                            int &startingPlayer) {
  for (unsigned int i = 0; i < auctionPlayers.size(); i++) {
    startingPlayer++;
    if (startingPlayer >= static_cast<int>(auctionPlayers.size())) {
      startingPlayer = 0;
      for (int j = 0; j < static_cast<int>(auctionPlayers.size()); j++) {
        if (!auctionPlayers[i].IsActive()) {
          auctionPlayers.erase(auctionPlayers.begin() + j);
          j = std::max(0, j - 1);
        }
      }
    }
    if (!auctionPlayers.at(static_cast<unsigned long>(startingPlayer)).IsActive()) {
      startingPlayer++;
    }
    if (auctionPlayers.at(static_cast<unsigned long>(startingPlayer)).IsActive()) {
      return &auctionPlayers[startingPlayer];
    }
  }
  return nullptr;
}

Monopoly::Player *Monopoly::Space::Property::DoAuction(std::vector<Player> &players, int &price, Player &startingPlayer) {
  std::vector<Player> auctionPlayers = players;
  for (int i = 0; i < static_cast<int>(auctionPlayers.size()); i++){
    if (!auctionPlayers[i].IsActive()){
      auctionPlayers.erase(auctionPlayers.begin() + i);
      i--;
    }
  }
  int currentVecPos;
  Player *currentAuctionPlayer = GetFirstActivePlayer(currentVecPos, auctionPlayers);
  int playerBid;
  int currentBid = 0;
  bool bidPlaced = false;
  int winningID;
  std::string winningName;
  std::cout << "Starting the auction for " << name << std::endl;
  while (!auctionPlayers.empty()) {
    if (!bidPlaced) {
      std::cout << "No one has bid on " << name << " [$ " << propertyCost << "] yet\n";
    } else {
      std::cout << "The current bid for " << name << " [$ " << propertyCost << "] is $"
                << currentBid << " by " << winningName << std::endl;
    }
    playerBid = GetBid(currentAuctionPlayer, currentBid);
    if (playerBid <= currentBid || currentAuctionPlayer->GetAmountMoney() < currentBid) {
      auctionPlayers.erase(auctionPlayers.begin() + currentVecPos);
      currentVecPos--;
    } else if (playerBid > currentBid) {
      currentBid = playerBid;
      winningID = currentAuctionPlayer->GetID();
      winningName = currentAuctionPlayer->GetName();
      bidPlaced = true;
    }
    if (auctionPlayers.size() == 1 && bidPlaced) {
      std::cout << winningName << " won " << name << " for $" << currentBid << std::endl;
      price = currentBid;
      return &(players[winningID]);
    }
    currentAuctionPlayer = GetNextAuctionPlayer(auctionPlayers, currentVecPos);
  }
  price = -1;
  std::cout << "No one decided to purchase " << name << std::endl;
  return nullptr;
}

void Monopoly::Space::Property::display() const {
  //Space Number | Space Name    | Owner | Upgrades | Players
  std::cout << name;
  PrintSpaces(Board::maxPropName - static_cast<int>(name.size()));
  if(owned){
    std::cout << " | " << ownedBy->GetName();
    PrintSpaces(Board::maxPlayerName - static_cast<int>(ownedBy->GetName().size()));
  }
  else {
    std::cout << " | None";
    PrintSpaces(Board::maxPlayerName - 4);
  }
  std::cout << " | ";
  PrintSpaces(8 - PrintUpgrades());
  std::cout << " | ";
  for(int i = 0; i < static_cast<int>(landedOnBy.size()) - 1; i++){
    landedOnBy[i]->PrintStats();
    std::cout << ", ";
  }
  if (!landedOnBy.empty()) landedOnBy[landedOnBy.size() - 1]->PrintStats();
  std::cout << std::endl;
}

void Monopoly::Space::Property::RemoveLander(Player *player) {
  for(int i = 0; i < static_cast<int>(landedOnBy.size()); i++){
    if(landedOnBy[i]->GetID() == player->GetID()){
      landedOnBy.erase(landedOnBy.begin() + i);
      return;
    }
  }
}

Monopoly::Player * Monopoly::Space::Property::GetFirstActivePlayer(int &index, std::vector<Player> &vect2Search) {
  for (int i = 0; i < static_cast<int>(playerRoster->size()); i++) {
    if (vect2Search.at(i).IsActive()){
      index = i;
      return &(vect2Search[i]);
    }
  }
  return nullptr;
}
