//
// Created by fidel on 1/8/18.
//

#ifndef HOARDING_USERINPUT_H
#define HOARDING_USERINPUT_H

#include <iostream>
#include "playerHandler.h"
//#include "boardHandler.h"
//#include "spaceClasses.h"
//#include "gameStateHandler.h"

namespace Monopoly {

int getUserTurn(const std::string &name);
int getNumPlayers();
bool offerBuy(const Monopoly::Player &currPlayer, const Monopoly::Space::Property &prop);
std::vector<std::string> GetPlayerNames(int numPlayers);
//TODO remedy output strings
}

#endif //HOARDING_USERINPUT_H
