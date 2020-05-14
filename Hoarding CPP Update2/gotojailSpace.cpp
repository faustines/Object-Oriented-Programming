//
// Created by fidel on 2/26/18.
//

#include "gotojailSpace.h"

Monopoly::Board *Monopoly::Space::GotoJail::boardSpaces = nullptr;

Monopoly::Space::GotoJail::GotoJail(std::string NAME, int INDEX){
  name = NAME;
  index = INDEX;
  type = SpaceType::GotoJail;
}

void Monopoly::Space::GotoJail::RemoveLander(Player *player) {
  for(int i = 0; i < static_cast<int>(landedOnBy.size()); i++){
    if(landedOnBy[i]->GetID() == player->GetID()){
      landedOnBy.erase(landedOnBy.begin() + i);
      return;
    }
  }
}

void Monopoly::Space::GotoJail::display() const {
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

void Monopoly::Space::GotoJail::activate(Monopoly::Player &activatingPlayer) {
  boardSpaces->RemoveLander(&activatingPlayer);
  static_cast<Space::Jail *>(boardSpaces->At(index))->AddPlayerToJail(activatingPlayer);
  activatingPlayer.SetCurrentPosition(index);
  std::cout << activatingPlayer.GetName()
            << ", you were sent to "
            << boardSpaces->At(index)->GetName()
            << " for "
            << activatingPlayer.TurnsInJail()
            << " turns\n";
}