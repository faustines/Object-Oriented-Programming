//
// Created by fidel on 1/8/18.
//

#ifndef HOARDING_USERINPUT_H
#define HOARDING_USERINPUT_H

#include <iostream>
#include "playerHandler.h"

namespace Monopoly {

int getUserTurn(const std::string &name);
int getNumPlayers();
bool offerBuy(const Monopoly::Player &currPlayer, const Monopoly::Space::Property &prop);
int GetPropToUpgrade(std::vector<Space *> &upgradeableSpaces);
int GetPropToDowngrade(std::vector<Space *> &downgradeableSpaces);
std::vector<std::string> GetPlayerNames(int numPlayers);
int GetBid (Player* player, int currentBid);
int EmergencyDowngrade(int owed, int current, std::vector<Space *> &downgradeableSpaces);
//TODO remedy output strings
}

#endif //HOARDING_USERINPUT_H
