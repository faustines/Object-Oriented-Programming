//
// Created by fidel on 1/10/18.
//

#include <iostream>
#include "diceHandler.h"

Monopoly::DiceRoller::DiceRoller(char *filename) {
  this->file.open(filename);
}

Monopoly::DiceRoller::~DiceRoller() {
  this->file.close();
}

int Monopoly::DiceRoller::GetRoll() {
  int roll1, roll2;
  if(file.good()) this->file >> roll1 >> roll2;
  else{std::cout << "GPG\n";}
  return ((roll1 % 6) + 1) + ((roll2 % 6) + 1);
}