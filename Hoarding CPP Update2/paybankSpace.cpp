//
// Created by fidel on 2/26/18.
//

#include "paybankSpace.h"
Monopoly::Rules *Monopoly::Space::PayToBank::rulesList = nullptr;
Monopoly::Board *Monopoly::Space::PayToBank::boardSpaces = nullptr;

Monopoly::Space::PayToBank::PayToBank(std::string NAME, int AMOUNT) : amount(AMOUNT){
  type = SpaceType::PayToBank;
  name = NAME;
}

void Monopoly::Space::PayToBank::activate(Player &activatingPlayer) {
  AddLander(&activatingPlayer);
  std::sort(landedOnBy.begin(), landedOnBy.end(), // Sort players by ID with lambda
            [](const Player *a, const Player *b) -> bool { return a->GetID() < b->GetID(); });
  if (amount > activatingPlayer.GetAmountMoney()) {
    boardSpaces->SellToSurvive(activatingPlayer, amount);
  }
  if (amount <= activatingPlayer.GetAmountMoney()) {
    activatingPlayer.TakeMoney(amount);
    if(rulesList->PutMoneyInFP()) Space::FreeParking::AddToPool(amount);
    std::cout << activatingPlayer.GetName() << " paid the bank $" << amount << " for landing on " << name << std::endl;
  } else {
    if(rulesList->PutMoneyInFP()) Monopoly::Space::FreeParking::AddToPool(activatingPlayer.GetAmountMoney());
    activatingPlayer.TerminatePlayer(*boardSpaces);
    std::cout << activatingPlayer.GetName() << " went bankrupt by landing on " << name << std::endl;
  }
}

void Monopoly::Space::PayToBank::display() const {
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

void Monopoly::Space::PayToBank::RemoveLander(Player *player) {
  for(int i = 0; i < static_cast<int>(landedOnBy.size()); i++){
    if(landedOnBy[i]->GetID() == player->GetID()){
      landedOnBy.erase(landedOnBy.begin() + i);
      return;
    }
  }
}