//
// Created by fidel on 2/25/18.
//

#include "freeparkingSpace.h"

int Monopoly::Space::FreeParking::pool = 0;

void Monopoly::Space::FreeParking::RemoveLander(Player *player) {
  for (int i = 0; i < static_cast<int>(landedOnBy.size()); i++) {
    if (landedOnBy[i]->GetID() == player->GetID()) {
      landedOnBy.erase(landedOnBy.begin() + i);
      return;
    }
  }
}

Monopoly::Space::FreeParking::FreeParking(std::string NAME) {
  type = SpaceType::FreeParking;
  name = std::move(NAME);
}

void Monopoly::Space::FreeParking::display() const {
  std::cout << name;
  PrintSpaces(Board::maxPropName - static_cast<int>(name.size()));
  std::cout << " | None";
  PrintSpaces(Board::maxPlayerName - 4);
  std::cout << " | ";
  PrintSpaces(8);
  std::cout << " | ";
  for(int i = 0; i < static_cast<int>(landedOnBy.size()) - 1; i++){
    landedOnBy[i]->PrintStats();
    std::cout << ", ";
  }
  if (!landedOnBy.empty()) landedOnBy[landedOnBy.size() - 1]->PrintStats();
  std::cout << std::endl;
}

void Monopoly::Space::FreeParking::activate(Monopoly::Player &activatingPlayer) {
  AddLander(&activatingPlayer);
  std::sort(landedOnBy.begin(), landedOnBy.end(), // Sort players by ID with lambda
            [](const Player *a, const Player *b) -> bool { return a->GetID() < b->GetID(); });
  if (pool > 0) {
    activatingPlayer.PayPlayer(pool);
    std::cout << activatingPlayer.GetName() << " got $" << pool << " for landing on " << name << std::endl;
    pool = 0;
  }
}

void Monopoly::Space::FreeParking::AddToPool(int amount) {
  Monopoly::Space::FreeParking::pool += amount;
}