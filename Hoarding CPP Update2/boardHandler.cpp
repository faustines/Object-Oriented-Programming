//
// Created by fidel on 1/9/18.
//

#include "boardHandler.h"

int Monopoly::Board::maxPlayerName = 0;
int Monopoly::Board::maxPropName = 0;

Monopoly::Board::Board(char *filename, int housesB4Hotel) : numHousesB4Hotel(housesB4Hotel) {
  int numSpaces;
  file.open(filename);
  file.ignore(256, ',');
  file >> numSpaces;
  std::string test;
  getline(file, test);
  getline(file, test);
  getline(file, test);
  getline(file, test);
  for (int i = 0; i < numSpaces + 1; i++) {
    std::string type = getNextCsv(file);
    if (type == "Property") {
      ReadInProp(file);
    } else if (type == "Go") {
      ReadInGo(file);
    } else if (type == "FreeParking"){
      ReadInFP(file);
    } else if (type == "Pay"){
      ReadInPay(file);
    } else if (type == "Jail"){
      ReadInJail(file);
    } else if (type == "GoToJail"){
      ReadInGotoJail(file);
    }
  }
}

Monopoly::Board::~Board() {
  file.close();
}

void Monopoly::Board::ReadInProp(std::ifstream &file) {
  std::string name;
  int setID, intrasetID, propertyCost, houseCost, hotelCost, rent, rentWithHouse, rentWithHotel;
  file >> setID;
  file.ignore();
  file >> intrasetID;
  file.ignore();
  name = getNextCsv(file);
  file >> propertyCost;
  file.ignore();
  file >> houseCost;
  file.ignore();
  file >> hotelCost;
  file.ignore();
  file >> rent;
  file.ignore();
  file >> rentWithHouse;
  file.ignore();
  file >> rentWithHotel;
  file.ignore();
  file.ignore();
  auto prop = std::make_unique<Space::Property>(setID,
                                                intrasetID,
                                                name,
                                                propertyCost,
                                                houseCost,
                                                hotelCost,
                                                rent,
                                                rentWithHouse,
                                                rentWithHotel,
                                                numHousesB4Hotel);
  properties.push_back(prop.get());
  board.push_back(std::move(prop));
}

void Monopoly::Board::ReadInGo(std::ifstream &file) {
  int salary;
  std::string name;
  file >> salary;
  file.ignore();
  name = getNextCsv(file);
  file.ignore(256, '\n');
  auto space = std::make_unique<Space::Go>(name, salary);
  board.push_back(std::move(space));
}

void Monopoly::Board::ReadInFP(std::ifstream &file) {
  std::string name;
  name = getNextCsv(file);
  file.ignore(256, '\n');
  auto space = std::make_unique<Space::FreeParking>(name);
  board.push_back(std::move(space));
}

void Monopoly::Board::ReadInPay(std::ifstream &file) {
  std::string name;
  int amount;
  name = getNextCsv(file);
  file >> amount;
  file.ignore(256, '\n');
  auto pay = std::make_unique<Space::PayToBank>(name, amount);
  board.push_back(std::move(pay));
}

void Monopoly::Board::ReadInJail(std::ifstream &file) {
  std::string name;
  int turnsInJail;
  int bail;
  name = getNextCsv(file);
  file >> turnsInJail;
  file.ignore();
  file >> bail;
  file.ignore(256, '\n');
  auto jail = std::make_unique<Space::Jail>(name, turnsInJail, bail);
  board.push_back(std::move(jail));
}

void Monopoly::Board::ReadInGotoJail(std::ifstream &file) {
  std::string name;
  int index;
  name = getNextCsv(file);
  file >> index;
  file.ignore(256, '\n');
  auto gotoJail = std::make_unique<Space::GotoJail>(name, index);
  board.push_back(std::move(gotoJail));
}

void Monopoly::Board::Print(std::vector<Player> &players) {
  maxPropName = GetLongestSpaceName();
  maxPlayerName = GetLongestPlayerName(players);
  std::cout << "Space Number | Space Name";
  PrintSpaces(maxPropName - 10);
  std::cout << " | Owner";
  PrintSpaces(maxPlayerName - 5);
  std::cout << " | Upgrades";
  std::cout << " | Players\n";
  for (unsigned int i = 0; i < board.size(); i++) {
    std::cout << i;
    PrintSpaces(12 - 1);
    std::cout << " | ";
    board[i]->display();
  }
}

int Monopoly::Board::GetLongestSpaceName() {
  unsigned int max = 10;
  for (std::unique_ptr<Space> &space : board) {
    if (space->GetName().size() > max) {
      max = static_cast<int>(space->GetName().size());
    }
  }
  return max;
}

int Monopoly::Board::GetLongestPlayerName(const std::vector<Monopoly::Player> &players) {
  unsigned int max = 5;
  for (const Monopoly::Player &player : players){
    if(player.GetName().size() > max){
      max = static_cast<int>(player.GetName().size());
    }
  }
  return max;
}

std::vector<int> Monopoly::Board::GetUniqueIDs(bool intraset) {
  std::map<int, bool> checked;
  std::vector<int> ids;
  if(intraset){
    for (const auto &prop : properties) {
      if (checked.count(prop->GetIntrasetID()) == 0) {
        ids.push_back(prop->GetIntrasetID());
        checked.emplace(prop->GetIntrasetID(), true);
      }
    }
  } else {
    for (const auto &prop : properties) {
      if (checked.count(prop->GetSetID()) == 0) {
        ids.push_back(prop->GetSetID());
        checked.emplace(prop->GetSetID(), true);
      }
    }
  }
  std::sort(ids.begin(), ids.end());
  return ids;
}

Monopoly::Player *Monopoly::Board::GetSetOwner(int setID) const {
  Player *ownerOfPreviousProp = nullptr;
  bool previousOwnerSet = false;
  for (auto &prop : properties) {
      if (prop->IsOwned() && !previousOwnerSet) {
        if(prop->GetSetID() == setID) {
          ownerOfPreviousProp = prop->GetOwner();
          previousOwnerSet = true;
        }
      } else {
        if(previousOwnerSet) {
          if(prop->GetSetID() == setID && prop->IsOwned()) {
            if(ownerOfPreviousProp->GetID() != prop->GetOwner()->GetID()) {
              return nullptr;
            }
          }
        }
      }
    if(prop->GetSetID() == setID && !prop->IsOwned()){
      return nullptr;
    }
  }
  return ownerOfPreviousProp;
}

void Monopoly::Board::ResetDanglingSpaces(const Player &player) {
  for(auto &prop : properties){
    if(prop->IsOwned() && prop->GetOwner()->GetID() == player.GetID()){
      prop->ResetOwner();
    }
  }
}

void Monopoly::Board::TransferProperties(Player &winner, int loserID) {
  for (auto &prop : properties) {
    if (prop->IsOwned() && prop->GetOwner()->GetID() == loserID){
      prop->SetOwner(&winner);
    }
  }

}

int Monopoly::Board::NumSpaces() const {
  return static_cast<int>(board.size());
}

Monopoly::SpaceType Monopoly::Board::GetType(int num) {
  return board.at(static_cast<unsigned int>(num))->GetType();
}

int Monopoly::Board::GetNumDigits(int num) {
  std::stringstream sstr;
  std::string str;
  sstr << num;
  sstr >> str;
  return static_cast<int>(str.size());
}

Monopoly::Space* Monopoly::Board::At(int num) {
  return board[num].get();
}

Monopoly::Space::Property *Monopoly::Board::GetProperty(int num) {
  return properties[num];
}

Monopoly::Space::Go* Monopoly::Board::GetGo() {
  if (board[0]->GetType() == SpaceType::Go){
        return static_cast<Space::Go*>(board[0].get());
    }
  else return nullptr;
}

int Monopoly::Board::NumProps() const {
  return static_cast<int>(properties.size());
}

std::vector<Monopoly::Space::Property *> Monopoly::Board::GetUpgradableProps(Player &player2Check,
                                                                                 bool buildEvenly,
                                                                                 bool downgradeOverride) {
  auto setIDs = GetUniqueIDs();
  std::vector<Monopoly::Space::Property *> upgradableProps;
  for (int i = 0; i < NumProps(); i++) {
    auto currProp = properties[i];
    if (currProp != nullptr) {
      if (currProp->IsOwned()) {
        if (currProp->GetOwner()->GetID() == player2Check.GetID()) {
          upgradableProps.push_back(properties[i]);
        }
      }
    }
  }
  upgradableProps.erase(std::remove_if(upgradableProps.begin(),
                                       upgradableProps.end(), // Drop props if player doesnt own whole set or cant afford it
                                       [&](Space::Property *i) {
                                         return (GetSetOwner(i->GetSetID()) == nullptr) ||
                                             (!downgradeOverride && ((i->CalcUpgradeCost()
                                                 > player2Check.GetAmountMoney()) || i->GetNumHotels() > 0));
                                       }),
                        upgradableProps.end());

  std::sort(upgradableProps.begin(), upgradableProps.end(), // Sort props by setID with lambda
            [](Space::Property *const a, Space::Property *const b) -> bool { return a->GetSetID() < b->GetSetID(); });
  int partition = 0;
  int lastID;
  if (!upgradableProps.empty()) lastID = upgradableProps[0]->GetSetID();
  for (int i = 0; i < static_cast<int>(upgradableProps.size()); i++) {
    if (upgradableProps[i]->GetSetID() != lastID) {
      lastID = upgradableProps[i]->GetSetID();
      std::sort(upgradableProps.begin() + partition,
                upgradableProps.begin() + i - 1, // Sort props by intrasetID with lambda
                [](Space::Property *const a, Space::Property *const b) -> bool { return a->GetIntrasetID() < b->GetIntrasetID(); });
      partition = i;
    }
  }
  std::sort(upgradableProps.begin() + partition, upgradableProps.end(), // Sort props by intrasetID with lambda
            [](Space::Property *const a, Space::Property *const b) -> bool { return a->GetIntrasetID() < b->GetIntrasetID(); });
  if (buildEvenly && !downgradeOverride) { // Drop props depending on upgrade evenly rule
    partition = 0;
    int currMin;
    if (!upgradableProps.empty()) lastID = upgradableProps[0]->GetSetID();
    for (int i = 0; i < static_cast<int>(upgradableProps.size()); i++) {
      if (upgradableProps[i]->GetSetID() != lastID) {
        lastID = upgradableProps[i]->GetSetID();
        currMin = upgradableProps[partition]->GetNumHouses();
        for (int j = partition; j < i; j++) {
          if (upgradableProps[j]->GetNumHouses() < currMin) {
            currMin = upgradableProps[j]->GetNumHouses();
          }
        }
        for (int j = partition; j < i; j++) {
          if (upgradableProps[j]->GetNumHouses() != currMin) {
            upgradableProps.erase(upgradableProps.begin() + j);
            j--;
            i--;
          }
        }
        partition = i;
      }
    }
    if (!upgradableProps.empty()) currMin = upgradableProps[partition]->GetNumHouses();
    for (int j = partition; j < static_cast<int>(upgradableProps.size()); j++) {
      if (upgradableProps[j]->GetNumHouses() < currMin) {
        currMin = upgradableProps[j]->GetNumHouses();
      }
    }
    for (int j = partition; j < static_cast<int>(upgradableProps.size()); j++) {
      if (upgradableProps[j]->GetNumHouses() != currMin) {
        upgradableProps.erase(upgradableProps.begin() + j);
        j--;
      }
    }
  }
  return upgradableProps;
}

std::vector<Monopoly::Space::Property *> Monopoly::Board::GetDowngradeableProps(Player &player2Check, bool buildEvenly) {
  auto downgradableProps = GetUpgradableProps(player2Check, buildEvenly, true);
  downgradableProps.erase(std::remove_if(downgradableProps.begin(),
                                         downgradableProps.end(), // Drop props no upgrades
                                         [&](Space::Property *i) {
                                           return (i->GetNumUpgrades() == 0);
                                         }),
                          downgradableProps.end());
  int partition = 0;
  int lastID;
  int currMax;
  if (buildEvenly) {
    if (!downgradableProps.empty()) lastID = downgradableProps[0]->GetSetID();
    for (int i = 0; i < static_cast<int>(downgradableProps.size()); i++) {
      if (downgradableProps[i]->GetSetID() != lastID) {
        lastID = downgradableProps[i]->GetSetID();
        currMax = downgradableProps[partition]->GetNumUpgrades();
        for (int j = partition; j < i; j++) {
          if (downgradableProps[j]->GetNumUpgrades() > currMax) {
            currMax = downgradableProps[j]->GetNumUpgrades();
          }
        }
        for (int j = partition; j < i; j++) {
          if (downgradableProps[j]->GetNumUpgrades() != currMax) {
            downgradableProps.erase(downgradableProps.begin() + j);
            j--;
            i--;
          }
        }
        partition = i;
      }
    }
    if (!downgradableProps.empty()) {
      currMax = downgradableProps[partition]->GetNumUpgrades();
    }
    for (int j = partition; j < static_cast<int>(downgradableProps.size()); j++) {
      if (downgradableProps[j]->GetNumUpgrades() > currMax) {
        currMax = downgradableProps[j]->GetNumUpgrades();
      }
    }
    for (int j = partition; j < static_cast<int>(downgradableProps.size()); j++) {
      if (downgradableProps[j]->GetNumUpgrades() != currMax) {
        downgradableProps.erase(downgradableProps.begin() + j);
        j--;
      }
    }
  }
  return downgradableProps;
}

void Monopoly::Board::SellToSurvive(Player &loser, int owed) {
  auto props = GetDowngradeableProps(loser, false);
  int choice;
  while (!props.empty() && loser.GetAmountMoney() < owed) {
    choice = EmergencyDowngrade(owed, loser.GetAmountMoney(), props);
    props[choice]->SellUpgrade();
    props = GetDowngradeableProps(loser, false);
  }
}

void Monopoly::Board::RemoveLander(Player *p2r) {
  board[p2r->GetCurrentPosition()]->RemoveLander(p2r);
}