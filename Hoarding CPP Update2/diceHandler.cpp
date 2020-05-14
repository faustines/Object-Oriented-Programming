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
  int roll;
  if(file.good()) this->file >> roll;
  else{std::cout << "BAD FILE\n";}
  return ((roll % 6) + 1);
}