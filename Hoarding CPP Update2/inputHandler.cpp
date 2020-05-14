//
// Created by fidel on 1/8/18.
//

#include "inputHandler.h"

int Monopoly::getUserTurn(const std::string &name) {
  int userChoice;
  std::cout << name << " please enter your move\n"
            << "1 to roll dice\n"
            << "2 to upgrade a property with a house or hotel\n"
            << "3 to sell a house or hotel\n"
            << "4 to leave the game\n"
            << "Your move: ";
  std::cin >> userChoice;
  return userChoice;
}

int Monopoly::getNumPlayers() {
  int numPlayers;
  std::cout << "Enter how many players will be playing: ";
  std::cin >> numPlayers;
  return numPlayers;
}

bool Monopoly::offerBuy(const Monopoly::Player &currPlayer, const Monopoly::Space::Property &prop) {
  char userAnswer;
  std::cout << "Would you like to buy " << prop.GetName() << " for $" << prop.GetCost() << "?" << std::endl;
  std::cout << "Rent on " << prop.GetName() << " is $" << prop.GetRent() << std::endl;
  std::cout << "Enter y for yes or n for no: ";
  std::cin >> userAnswer;
  return (toupper(userAnswer) == 'Y');
}

std::vector<std::string> Monopoly::GetPlayerNames(int numPlayers) {
  std::vector<std::string> names;
  std::string name;
  for (int i = 0; i < numPlayers; i++) {
    std::cout << "Enter the name of player " << i + 1 << ": ";
    std::cin >> name;
    names.push_back(name);
  }
  return names;
}

int Monopoly::GetPropToUpgrade(std::vector<Space::Property *> &upgradeableSpaces) {
  int choice;
  if (upgradeableSpaces.empty()) {
    std::cout << "You don't have any properties that you can upgrade\n";
    return -1;
  } else {
    std::cout << "Which property do you want to upgrade?" << std::endl;
    for (int i = 0; i < static_cast<int>(upgradeableSpaces.size()); i++) {
      std::cout << i << ". " << upgradeableSpaces[i]->GetName() << " [$"
                << upgradeableSpaces[i]->CalcUpgradeCost() << ']' << std::endl;
    }
    std::cout << "Your choice: ";
  }
  std::cin >> choice;
  return choice;
}

int Monopoly::GetPropToDowngrade(std::vector<Space::Property *> &downgradeableSpaces) {
  int choice;
  if (downgradeableSpaces.empty()) {
    std::cout << "You don't have any upgrades that you can sell\n";
    return -1;
  } else {
    std::cout << "Which property do you want to downgrade?" << std::endl;
    for (int i = 0; i < static_cast<int>(downgradeableSpaces.size()); i++) {
      std::cout << i << ". " << downgradeableSpaces[i]->GetName() << " [$"
                << downgradeableSpaces[i]->CalcValDowngrade() << ']' << std::endl;
    }
    std::cout << "Your choice: ";
  }
  std::cin >> choice;
  return choice;
}

int Monopoly::GetBid(Player *player, int currentBid) {
  int bid = 0;
  std::cout << player->GetName() << ", enter a bid of at least $" << currentBid + 1
            << " to bid on the property or a value less than that to leave the auction\nYour bid: ";
  std::cin >> bid;
  return bid;
}

int Monopoly::EmergencyDowngrade(int owed, int current, std::vector<Space::Property *> &downgradeableSpaces) {
  int choice;
  if (downgradeableSpaces.empty()) {
    return -1;
  } else {
    std::cout << "You have $" << current << " but you owe $" << owed
              << "\nPick an upgrade to sell to make up the difference" << std::endl;
    for (int i = 0; i < static_cast<int>(downgradeableSpaces.size()); i++) {
      std::cout << i << ". " << downgradeableSpaces[i]->GetName() << " [$"
                << downgradeableSpaces[i]->CalcValDowngrade() << ']' << std::endl;
    }
    std::cout << "Your choice: ";
  }
  std::cin >> choice;
  return choice;
}

void Monopoly::PrintSpaces(int num) {
  for (int i = 0; i < num; i++) {
    std::cout << " ";
  }
}

int Monopoly::GetJailTurn(std::string name, int bail) {
  if(PayJailPrompt(bail)){
    return -1;
  } else {
    return getUserTurn(name);
  }
}

bool Monopoly::PayJailPrompt(int bail) {
  std::string answer;
  std::cout << "Would you like to pay $"
            << bail
            << " to leave jail early?\n"
            << "y for yes and n for no: ";
  std::cin >> answer;
  return toupper(answer[0]) == 'Y';
}