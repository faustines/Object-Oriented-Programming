//
// Created by fidel on 1/9/18.
//

#include "boardHandler.h"

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
  auto prop = std::make_shared<Space::Property>(setID,
                                                intrasetID,
                                                name,
                                                propertyCost,
                                                houseCost,
                                                hotelCost,
                                                rent,
                                                rentWithHouse,
                                                rentWithHotel,
                                                numHousesB4Hotel);
  board.emplace_back(prop);
}

void Monopoly::Board::ReadInGo(std::ifstream &file) {
  int salary;
  std::string name;
  file >> salary;
  file.ignore();
  name = getNextCsv(file);
  file.ignore(256, '\n');
  auto space = std::make_shared<Space::Go>(name, salary);
  board.emplace_back(space);
}

void Monopoly::Board::Print(std::vector<Player> &players) {
  int maxPropName = GetLongestPropName();
  int maxPlayerName = GetLongestPlayerName(players);
  std::string nameToPrint;
  std::cout << "Space Number | Space Name";
  PrintSpaces(maxPropName - 10);
  std::cout << " | Owner";
  PrintSpaces(maxPlayerName - 5);
  std::cout << " | Upgrades";
  std::cout << " | Players\n";
  for (unsigned int i = 0; i < board.size(); i++) {
    std::cout << i;
    PrintSpaces(12 - GetNumDigits(static_cast<int>(board.size()) - 1));
    std::cout << " | " << board.at(i)->GetName();
    PrintSpaces(maxPropName - static_cast<int>( board.at(i)->GetName().length()));
    std::cout << " | ";
    if(board.at(i)->GetType() == SpaceType::Go || !board.at(i)->IsOwned()){
      nameToPrint = "None";
    } else {
      nameToPrint = board.at(i)->GetOwner()->GetName();
    }
    std::cout << nameToPrint;
    PrintSpaces(maxPlayerName - static_cast<int>(nameToPrint.length()));
    std::cout << " | ";
    if(board[i]->GetType() == SpaceType::Property)dynamic_cast<Space::Property*>(board[i].get())->PrintUpgrades();
    std::cout << " | ";
    bool printed = false;
    for (const Player &player : players) {
      if (player.IsActive() && static_cast<int>(i) == player.GetCurrentPos()) {
        if(printed) std::cout << ", ";
        player.PrintStats();
        printed = true;
      }
    }
      std::cout << std::endl;
  }
}

int Monopoly::Board::GetLongestPropName() {
  unsigned int max = 10;
  for (std::shared_ptr<Space> &space : board) {
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
    for (const std::shared_ptr<Space> &space : board) {
      if (space->GetType() == SpaceType::Property && checked.count(space->GetIntrasetID()) == 0) {
        ids.push_back(space->GetIntrasetID());
        checked.emplace(space->GetIntrasetID(), true);
      }
    }
  } else {
    for (const std::shared_ptr<Space> &space : board) {
      if (space->GetType() == SpaceType::Property && checked.count(space->GetSetID()) == 0) {
        ids.push_back(space->GetSetID());
        checked.emplace(space->GetSetID(), true);
      }
    }
  }
  std::sort(ids.begin(), ids.end());
  return ids;
}

Monopoly::Player *Monopoly::Board::GetSetOwner(int setID) const {
  Player *ownerOfPreviousProp = nullptr;
  bool previousOwnerSet = false;
  for (auto &space : board) {
      if (space->IsOwned() && !previousOwnerSet) {
        if(space->GetSetID() == setID) {
          ownerOfPreviousProp = space->GetOwner();
          previousOwnerSet = true;
        }
      } else {
        if(previousOwnerSet && space->GetType() == SpaceType::Property) {
          if(space->GetSetID() == setID && space->IsOwned()) {
            if(ownerOfPreviousProp->GetID() != space->GetOwner()->GetID()) {
              return nullptr;
            }
          }
        }
      }
    if(space->GetSetID() == setID && !space->IsOwned()){
      return nullptr;
    }
  }
  return ownerOfPreviousProp;
}

void Monopoly::Board::ResetDanglingSpaces(const Player &player) {
  for(std::shared_ptr<Monopoly::Space> &space : board){
    if(space->IsOwned() && space->GetOwner()->GetID() == player.GetID()){
      space->ResetOwner();
    }
  }
}

void Monopoly::Board::TransferProperties(Player &winner, int loserID) {
  for (std::shared_ptr<Monopoly::Space> &space : board) {
    if (space->IsOwned() && space->GetOwner()->GetID() == loserID){
      space->SetOwner(&winner);
    }
  }

}

int Monopoly::Board::NumSpaces() const {
  return static_cast<int>(board.size());
}

Monopoly::SpaceType Monopoly::Board::GetType(int num) {
  return board.at(static_cast<unsigned int>(num))->GetType();
}

std::shared_ptr<Monopoly::Space::Property> Monopoly::Board::GetProperty(int num) const {
  return std::dynamic_pointer_cast<Monopoly::Space::Property>(board.at(static_cast<unsigned int>(num)));
}

std::shared_ptr<Monopoly::Space::Go> Monopoly::Board::GetGo() const {
  if (board.at(0)->GetType() != SpaceType::Go){
    throw std::runtime_error("No GO on board");
  }
  return std::dynamic_pointer_cast<Monopoly::Space::Go>(board.at(0));
}

std::shared_ptr<Monopoly::Space> Monopoly::Board::GetSpace(int num) const {
  return board.at(static_cast<unsigned int>(num));
}

void Monopoly::Board::PrintSpaces(int c) {
  for (int i = 0; i < c; i++) {
    std::cout << " ";
  }
}

int Monopoly::Board::GetNumDigits(int num) {
  std::stringstream sstr;
  std::string str;
  sstr << num;
  sstr >> str;
  return static_cast<int>(str.size());
}

std::vector<std::shared_ptr<Monopoly::Space>> Monopoly::Board::GetBoard() {
  return board;
}