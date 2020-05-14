//
// Created by fidel on 1/8/18.
//

#include "inputHandler.h"

int Monopoly::getUserTurn(const std::string &name) {
  int userChoice;
  std::cout << name << " please enter your move\n";
  std::cout << "1 to roll dice\n";
  std::cout << "2 to leave the game\n";
  std::cout << "Your move: ";
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

std::vector<std::string> Monopoly::GetPlayerNames(int numPlayers){
  std::vector<std::string> names;
  std::string name;
  for(int i = 0; i < numPlayers; i++){
    std::cout << "Enter the name of player " << i + 1 << ": ";
    std::cin >> name;
    names.push_back(name);
  }
  return names;
}