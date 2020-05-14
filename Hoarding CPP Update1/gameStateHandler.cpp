//
// Created by fidel on 1/31/18.
//

#include "gameStateHandler.h"
Monopoly::Gamestate::Gamestate(char **args) : currentPlayer(nullptr) {
  rules = std::make_unique<Monopoly::Rules>(args[1]);
  dice = std::make_unique<Monopoly::DiceRoller>(args[3]);
  board = std::make_unique<Monopoly::Board>(args[2], rules->GetNumHousesB4Hotel());
  numTurnsLeft = rules->numTurns();
  currPlayerNum = 0;
  playerTerminatedThisTurn = false;
  numRollsThisTurn = 0;
  rolledDoubles = false;
}

Monopoly::Gamestate::~Gamestate() = default;

bool Monopoly::Gamestate::gameActive() {
  return CountActivePlayers() > rules->numPlayersToEnd() && (numTurnsLeft == -1 || numTurnsLeft > 0);
}

void Monopoly::Gamestate::inputExecutor(int userChoice) {
  int roll, roll1, roll2;
  playerTerminatedThisTurn = false;
  auto currProp = board->GetProperty(currentPlayer->GetCurrentPosition());
  auto currSpace = board->GetSpace(currentPlayer->GetCurrentPosition());
  //===========================================User Choice 4==========================================================//
  if (userChoice == 4) {
    currentPlayer->TerminatePlayer(*board);
    currentPlayer = GetNextPlayer();
    playerTerminatedThisTurn = true;
    numRollsThisTurn = 0;
  }
    //===========================================User Choice 1==========================================================//
  else if (userChoice == 1) {
    if (rules->numTurns() != -1) numTurnsLeft--;
    roll1 = dice->GetRoll();
    roll2 = dice->GetRoll();
    roll = roll1 + roll2;
    movePlayer(roll);
    currSpace = board->GetSpace(currentPlayer->GetCurrentPosition());
    currProp = board->GetProperty(currentPlayer->GetCurrentPosition());
    std::cout << currentPlayer->GetName() << ", you rolled a " << roll << std::endl;
    numRollsThisTurn++;
    if (currSpace->GetType() == SpaceType::Property
        && currProp->IsOwned() && currProp->GetOwner()->GetID() != currentPlayer->GetID()) {
      landedOnOtherPlayersSpace();
    } else if (currSpace->GetType() == SpaceType::Property && !currSpace->IsOwned()) {
      landedOnUnownedSpace();
    } else if (currSpace->IsOwned() && currSpace->GetOwner()->GetID() == currentPlayer->GetID()) {
      std::cout << currentPlayer->GetName() << ", you landed on " << currSpace->GetName() << " which you already own\n";
    }
    //==========================================User Choice 2=========================================================//
  } else if (userChoice == 2) {
    auto props = GetUpgradableProps(*currentPlayer, rules->BuildHousesEvenly());
    int upgradeChoice = Monopoly::GetPropToUpgrade(props);
    if (upgradeChoice != -1) {
      dynamic_cast<Space::Property *>(props[upgradeChoice])->BuyUpgrade();
    }
    //=========================================User Choice 3==========================================================//
  } else if (userChoice == 3) {
    auto props = GetDowngradeableProps(*currentPlayer, rules->BuildHousesEvenly());
    int downgradeChoice = Monopoly::GetPropToDowngrade(props);
    if (downgradeChoice != -1) {
      dynamic_cast<Space::Property *>(props[downgradeChoice])->SellUpgrade();
    }
  } else {
    std::cout << "Unrecognized move number " << userChoice << " in Move constructor\n";
  }
  //============================================End User Choices======================================================//
  if ((!playerTerminatedThisTurn && numRollsThisTurn > rules->GetMaxRerolls()) || (roll1 != roll2 && userChoice == 1)) {
    currentPlayer = GetNextPlayer();
    numRollsThisTurn = 0;
  }
}

void Monopoly::Gamestate::landedOnOtherPlayersSpace() {
  int rent = board->GetProperty(currentPlayer->GetCurrentPosition())->CalcRent(rules->setMultiplier(), *board);
  if (rent > currentPlayer->GetAmountMoney()) {
    SellToSurvive(*currentPlayer, rent);
  }
  if (board->GetProperty(currentPlayer->GetCurrentPosition())->PayRent(*currentPlayer,
                                                                       rules->setMultiplier(),
                                                                       *board,
                                                                       rent)) {
    std::cout << currentPlayer->GetName() << " paid "
              << board->GetProperty(currentPlayer->GetCurrentPosition())->GetOwner()->GetName() << " $" << rent
              << " for landing on "
              << board->GetProperty(currentPlayer->GetCurrentPosition())->GetName() << std::endl;
  } else {
    currentPlayer->TerminatePlayer(*board->GetProperty(currentPlayer->GetCurrentPosition())->GetOwner(), *board);
  }
}

void Monopoly::Gamestate::landedOnUnownedSpace() {
  int winningPrice = 0;
  auto prop = board->GetProperty(currentPlayer->GetCurrentPosition());
  if (board->GetSpace(currentPlayer->GetCurrentPosition())->GetType() == SpaceType::Property &&
      !prop->IsOwned() && currentPlayer->GetAmountMoney() >= prop->GetCost()) {
    //Property is unowned and player has enough money to buy
    if (Monopoly::offerBuy(*currentPlayer, *board->GetProperty(currentPlayer->GetCurrentPosition()))) {
      prop->SetOwner(currentPlayer);
      currentPlayer->TakeMoney(board->GetProperty(currentPlayer->GetCurrentPosition())->GetCost());
      std::cout << currentPlayer->GetName() << " bought "
                << prop->GetName() << " for $"
                << prop->GetCost() << std::endl;
    } else if (rules->AuctionProps()) {
      Player *winner = DoAuction(*board->GetProperty(currentPlayer->GetCurrentPosition()), winningPrice, currentPlayer);
      if (winner != nullptr) {
        winner->TakeMoney(winningPrice);
        prop->SetOwner(winner);
      }
    }
  } else if (!prop->IsOwned()
      && currentPlayer->GetAmountMoney() < prop->GetCost()) {
    std::cout << currentPlayer->GetName() << ", you don't have enough money to afford "
              << prop->GetName() << ".\n";
    std::cout << prop->GetName() << " costs $"
              << prop->GetCost() << " but you only have $"
              << currentPlayer->GetAmountMoney() << std::endl;
  }
}

int Monopoly::Gamestate::CountActivePlayers() const {
  int count = 0;
  for (const Player &player : players) {
    if (player.IsActive()) count++;
  }
  return count;
}

Monopoly::Player *Monopoly::Gamestate::GetNextPlayer() {
  for (unsigned int i = 0; i < players.size(); i++) {
    currPlayerNum++;
    if (currPlayerNum >= static_cast<int>(players.size())) {
      currPlayerNum = 0;
    }
    if (!players.at(static_cast<unsigned long>(currPlayerNum)).IsActive()) {
      currPlayerNum++;
    }
    if (players.at(static_cast<unsigned long>(currPlayerNum)).IsActive()) {
      return &players[currPlayerNum];
    }
  }
  throw std::runtime_error("No more active players exist");
}

void Monopoly::Gamestate::movePlayer(int roll) {
  int newPosition = currentPlayer->GetCurrentPosition() + roll;
  int goSalary;
  if (newPosition > board->NumSpaces() - 1) {
    goSalary = board->GetGo()->GetSalary();
    if (board->GetType(0) == SpaceType::Go) {
      currentPlayer->PayPlayer(goSalary * (newPosition / board->NumSpaces()));
    }
    currentPlayer->SetCurrentPosition(newPosition % board->NumSpaces());
    if (currentPlayer->GetCurrentPosition() == 0 && board->GetType(0) == SpaceType::Go) {
      currentPlayer->PayPlayer(static_cast<int>(goSalary * rules->goMultiplier()) - goSalary);
    }
  } else {
    currentPlayer->SetCurrentPosition(newPosition);
  }
}

void Monopoly::Gamestate::InitGame() {
  int numPlayers = getNumPlayers();
  std::vector<std::string> names = GetPlayerNames(numPlayers);
  for (const std::string &name : names) {
    players.emplace_back(Player(name, rules->startingCash()));
  }
  currentPlayer = &players[0];
}
int Monopoly::Gamestate::UserTurn() {
  return getUserTurn(currentPlayer->GetName());
}

void Monopoly::Gamestate::Print() {
  board->Print(players);
}

void Monopoly::Gamestate::PrintWinners() {
  int winningAmount = GetHighestNetworth();
  std::cout << "The winners are\n";
  for (Player &player : players) {
    if (getNetWorth(player) == winningAmount) {
      std::cout << player.GetName() << std::endl;
    }
  }
}

int Monopoly::Gamestate::getTotalPropValue(const Player &player) {
  int val = 0;
  for (int i = 0; i < board->NumSpaces(); i++) {
    if (board->GetSpace(i)->IsOwned() && board->GetProperty(i)->GetOwner()->GetID() == player.GetID()) {
      val += board->GetProperty(i)->GetCost();
      val += board->GetProperty(i)->GetValUpgrades();
    }
  }
  return val;
}

int Monopoly::Gamestate::getNetWorth(const Player &player) {
  return player.GetAmountMoney() + getTotalPropValue(player);
}

int Monopoly::Gamestate::GetHighestNetworth() {
  int max = 0;
  for (const Player &player : players) {
    int test = getNetWorth(player);
    if (player.IsActive() && test > max) max = test;
  }
  return max;
}

std::vector<Monopoly::Space *> Monopoly::Gamestate::GetUpgradableProps(Player &player2Check,
                                                                       bool buildEvenly,
                                                                       bool downgradeOverride) {
  auto setIDs = board->GetUniqueIDs();
  std::vector<Monopoly::Space *> upgradableProps;
  for (int i = 0; i < board->NumSpaces(); i++) {
    auto currProp = board->GetProperty(i);
    if (currProp != nullptr) {
      if (currProp->IsOwned()) {
        if (currProp->GetOwner()->GetID() == player2Check.GetID()) {
          upgradableProps.push_back(board->GetSpace(i).get());
        }
      }
    }
  }
  upgradableProps.erase(std::remove_if(upgradableProps.begin(),
                                       upgradableProps.end(), // Drop props if player doesnt own whole set or cant afford it
                                       [&](Space *i) {
                                         return (board->GetSetOwner(i->GetSetID()) == nullptr) ||
                                             (!downgradeOverride && ((dynamic_cast<Space::Property *>(i)->CalcUpgradeCost()
                                                 > player2Check.GetAmountMoney()) ||
                                                 dynamic_cast<Space::Property *>(i)->GetNumHotels() > 0));
                                       }),
                        upgradableProps.end());

  std::sort(upgradableProps.begin(), upgradableProps.end(), // Sort props by setID with lambda
            [](Space *const a, Space *const b) -> bool { return a->GetSetID() < b->GetSetID(); });
  int partition = 0;
  int lastID;
  if (!upgradableProps.empty()) lastID = upgradableProps[0]->GetSetID();
  for (int i = 0; i < static_cast<int>(upgradableProps.size()); i++) {
    if (upgradableProps[i]->GetSetID() != lastID) {
      lastID = upgradableProps[i]->GetSetID();
      std::sort(upgradableProps.begin() + partition,
                upgradableProps.begin() + i - 1, // Sort props by intrasetID with lambda
                [](Space *const a, Space *const b) -> bool { return a->GetIntrasetID() < b->GetIntrasetID(); });
      partition = i;
    }
  }
  std::sort(upgradableProps.begin() + partition, upgradableProps.end(), // Sort props by intrasetID with lambda
            [](Space *const a, Space *const b) -> bool { return a->GetIntrasetID() < b->GetIntrasetID(); });
  if (buildEvenly && !downgradeOverride) { // Drop props depending on upgrade evenly rule
    partition = 0;
    int currMin;
    if (!upgradableProps.empty()) lastID = upgradableProps[0]->GetSetID();
    for (int i = 0; i < static_cast<int>(upgradableProps.size()); i++) {
      if (upgradableProps[i]->GetSetID() != lastID) {
        lastID = upgradableProps[i]->GetSetID();
        currMin = dynamic_cast<Space::Property *>(upgradableProps[partition])->GetNumHouses();
        for (int j = partition; j < i; j++) {
          if (dynamic_cast<Space::Property *>(upgradableProps[j])->GetNumHouses() < currMin) {
            currMin = dynamic_cast<Space::Property *>(upgradableProps[j])->GetNumHouses();
          }
        }
        for (int j = partition; j < i; j++) {
          if (dynamic_cast<Space::Property *>(upgradableProps[j])->GetNumHouses() != currMin) {
            upgradableProps.erase(upgradableProps.begin() + j);
            j--;
            i--;
          }
        }
        partition = i;
      }
    }
    if (!upgradableProps.empty()) currMin = dynamic_cast<Space::Property *>(upgradableProps[partition])->GetNumHouses();
    for (int j = partition; j < static_cast<int>(upgradableProps.size()); j++) {
      if (dynamic_cast<Space::Property *>(upgradableProps[j])->GetNumHouses() < currMin) {
        currMin = dynamic_cast<Space::Property *>(upgradableProps[j])->GetNumHouses();
      }
    }
    for (int j = partition; j < static_cast<int>(upgradableProps.size()); j++) {
      if (dynamic_cast<Space::Property *>(upgradableProps[j])->GetNumHouses() != currMin) {
        upgradableProps.erase(upgradableProps.begin() + j);
        j--;
      }
    }
  }
  return upgradableProps;
}

std::vector<Monopoly::Space *> Monopoly::Gamestate::GetDowngradeableProps(Player &player2Check, bool buildEvenly) {
  auto downgradableProps = GetUpgradableProps(player2Check, buildEvenly, true);
  downgradableProps.erase(std::remove_if(downgradableProps.begin(),
                                         downgradableProps.end(), // Drop props no upgrades
                                         [&](Space *i) {
                                           return (dynamic_cast<Space::Property *>(i)->GetNumUpgrades() == 0);
                                         }),
                          downgradableProps.end());
  int partition = 0;
  int lastID;
  int currMax;
  if (buildEvenly) {
    if (!downgradableProps.empty()) lastID = downgradableProps[0]->GetSetID();
    for (int i = 0; i < static_cast<int>(downgradableProps.size()); i++) {
      if (downgradableProps[i]->GetSetID() != lastID) {
        lastID = downgradableProps[i]->GetSetID();
        currMax = dynamic_cast<Space::Property *>(downgradableProps[partition])->GetNumUpgrades();
        for (int j = partition; j < i; j++) {
          if (dynamic_cast<Space::Property *>(downgradableProps[j])->GetNumUpgrades() > currMax) {
            currMax = dynamic_cast<Space::Property *>(downgradableProps[j])->GetNumUpgrades();
          }
        }
        for (int j = partition; j < i; j++) {
          if (dynamic_cast<Space::Property *>(downgradableProps[j])->GetNumUpgrades() != currMax) {
            downgradableProps.erase(downgradableProps.begin() + j);
            j--;
            i--;
          }
        }
        partition = i;
      }
    }
    if (!downgradableProps.empty()) {
      currMax = dynamic_cast<Space::Property *>(downgradableProps[partition])->GetNumUpgrades();
    }
    for (int j = partition; j < static_cast<int>(downgradableProps.size()); j++) {
      if (dynamic_cast<Space::Property *>(downgradableProps[j])->GetNumUpgrades() > currMax) {
        currMax = dynamic_cast<Space::Property *>(downgradableProps[j])->GetNumUpgrades();
      }
    }
    for (int j = partition; j < static_cast<int>(downgradableProps.size()); j++) {
      if (dynamic_cast<Space::Property *>(downgradableProps[j])->GetNumUpgrades() != currMax) {
        downgradableProps.erase(downgradableProps.begin() + j);
        j--;
      }
    }
  }
  return downgradableProps;
}

Monopoly::Player *Monopoly::Gamestate::GetNextAuctionPlayer(std::vector<Monopoly::Player> &auctionPlayers,
                                                            int &startingPlayer) {
  for (unsigned int i = 0; i < auctionPlayers.size(); i++) {
    startingPlayer++;
    if (startingPlayer >= static_cast<int>(auctionPlayers.size())) {
      startingPlayer = 0;
      for (int j = 0; j < static_cast<int>(auctionPlayers.size()); j++) {
        if (!auctionPlayers[i].IsActive()) {
          auctionPlayers.erase(auctionPlayers.begin() + j);
          j = std::max(0, j - 1);
        }
      }
    }
    if (!auctionPlayers.at(static_cast<unsigned long>(startingPlayer)).IsActive()) {
      startingPlayer++;
    }
    if (auctionPlayers.at(static_cast<unsigned long>(startingPlayer)).IsActive()) {
      return &auctionPlayers[startingPlayer];
    }
  }
  return nullptr;
}

Monopoly::Player *Monopoly::Gamestate::DoAuction(const Space::Property &aucprop, int &price, Player *startingPlayer) {
  int currentVecPos = startingPlayer->GetID();
  std::vector<Player> auctionPlayers = players;
  int playerBid;
  int currentBid = 0;
  bool bidPlaced = false;
  Player *currentAuctionPlayer = startingPlayer;//, *highestBidder = nullptr;
  int winningID;
  std::string winningName;
  std::cout << "Starting the auction for " << aucprop.GetName() << std::endl;
  while (!auctionPlayers.empty()) {
    if (!bidPlaced) {
      std::cout << "No one has bid on " << aucprop.GetName() << " [$ " << aucprop.GetCost() << "] yet\n";
    } else {
      std::cout << "The current bid for " << aucprop.GetName() << " [$ " << aucprop.GetCost() << "] is $"
                << currentBid << " by " << winningName << std::endl;
    }
    playerBid = GetBid(currentAuctionPlayer, currentBid);
    if (playerBid <= currentBid || currentAuctionPlayer->GetAmountMoney() < currentBid) {
      auctionPlayers.erase(auctionPlayers.begin() + currentVecPos);
      currentVecPos--;
    } else if (playerBid > currentBid) {
      currentBid = playerBid;
      winningID = currentAuctionPlayer->GetID();
      winningName = currentAuctionPlayer->GetName();
      bidPlaced = true;
    }
    if (auctionPlayers.size() == 1 && bidPlaced) {
      std::cout << winningName << " won " << aucprop.GetName() << " for $" << currentBid << std::endl;
      price = currentBid;
      return &(players[winningID]);
    }
    currentAuctionPlayer = GetNextAuctionPlayer(auctionPlayers, currentVecPos);
  }
  price = -1;
  std::cout << "No one decided to purchase " << aucprop.GetName() << std::endl;
  return nullptr;
}

void Monopoly::Gamestate::SellToSurvive(Player &loser, int owed) {
  auto props = GetDowngradeableProps(loser, false);
  int choice;
  while (!props.empty() && loser.GetAmountMoney() < owed) {
    choice = EmergencyDowngrade(owed, loser.GetAmountMoney(), props);
    dynamic_cast<Space::Property *>(props[choice])->SellUpgrade();
    props = GetDowngradeableProps(loser, false);
  }
}