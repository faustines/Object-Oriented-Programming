//
// Created by fidel on 2/26/18.
//

#include "jailSpace.h"

Monopoly::Space::Jail::Jail(std::string NAME, int TURNS, int MONEY2LEAVE){
  name = NAME;
  turnsInJail = TURNS;
  bailAmount = MONEY2LEAVE;
  type = SpaceType::Jail;
}

void Monopoly::Space::Jail::RemoveLander(Player *player) {
  for(int i = 0; i < static_cast<int>(landedOnBy.size()); i++){
    if(landedOnBy[i]->GetID() == player->GetID()){
      landedOnBy.erase(landedOnBy.begin() + i);
      return;
    }
  }
}

void Monopoly::Space::Jail::display() const {
  //Space Number | Space Name    | Owner | Upgrades | Players
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

void Monopoly::Space::Jail::activate(Monopoly::Player &activatingPlayer) {
  AddLander(&activatingPlayer);
  std::sort(landedOnBy.begin(), landedOnBy.end(), // Sort players by ID with lambda
            [](const Player *a, const Player *b) -> bool { return a->GetID() < b->GetID(); });
}

void Monopoly::Space::Jail::AddPlayerToJail(Player &criminal) {
  criminal.PutInJail(turnsInJail, bailAmount); // TODO placemarker if something goes wrong
  AddLander(&criminal);
}
