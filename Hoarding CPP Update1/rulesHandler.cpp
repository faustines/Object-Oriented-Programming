//
// Created by fidel on 1/10/18.
//

#include "rulesHandler.h"

Monopoly::Rules::Rules(char *filename) {
  file.open(filename);
  file.ignore(256, ':');
  file >> sCash;
  file.ignore(256, ':');
  file >> turnLimit;
  file.ignore(256, ':');
  file >> numPlayers2End;
  file.ignore(256, ':');
  file >> propSetMult;
  file.ignore(256, ':');
  file >> numHousesB4Hotel;
  file.ignore(256, ':');
  file >> temp;
  mustBuildHousesEvenly = (toupper(temp[0]) == 'Y');
  file.ignore(256, ':');
  file >> temp;
  putMoneyInFP = (toupper(temp[0]) == 'Y');
  file.ignore(256, ':');
  file >> temp;
  auctionProp = (toupper(temp[0]) == 'Y');
  file.ignore(256, ':');
  file >> salaryMultLandGo;
  file.ignore(256, ':');
  file >> maxRerolls;
  file.close();
}

void Monopoly::Rules::Print() {
  std::cout << "Starting Cash: " << sCash << std::endl;
  std::cout << "Turn Limit (-1 for no turn limit): " << turnLimit << std::endl;
  std::cout << "Number of Players Left To End Game: " << numPlayers2End << std::endl;
  std::cout << "Property Set Multiplier: " << propSetMult << std::endl;
  std::cout << "Number of Houses Before Hotels: " << numHousesB4Hotel << std::endl;
  std::cout << "Must Build Houses Evenly: " << mustBuildHousesEvenly << std::endl;
  std::cout << "Put Money In Free Parking: " << putMoneyInFP << std::endl;
  std::cout << "Auction Properties: " << auctionProp << std::endl;
  std::cout << "Salary Multiplier For Landing On Go: " << salaryMultLandGo << std::endl;
  std::cout << "Max Doubles ReRolls: " << maxRerolls << std::endl;
}

int Monopoly::Rules::startingCash() {
  return sCash;
}

int Monopoly::Rules::numPlayersToEnd()  {
  return numPlayers2End;
}

int Monopoly::Rules::numTurns()  {
  return turnLimit;
}

double Monopoly::Rules::setMultiplier() {
  return propSetMult;
}

double Monopoly::Rules::goMultiplier() {
  return salaryMultLandGo;
}

int Monopoly::Rules::GetMaxRerolls() {
  return maxRerolls;
}

bool Monopoly::Rules::BuildHousesEvenly() {
  return mustBuildHousesEvenly;
}

int Monopoly::Rules::GetNumHousesB4Hotel() {
  return numHousesB4Hotel;
}

bool Monopoly::Rules::AuctionProps() {
  return auctionProp;
}