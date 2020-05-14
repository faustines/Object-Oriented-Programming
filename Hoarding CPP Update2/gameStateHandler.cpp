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
}

Monopoly::Gamestate::~Gamestate() = default;

bool Monopoly::Gamestate::gameActive() {
  return CountActivePlayers() > rules->numPlayersToEnd() && (numTurnsLeft == -1 || numTurnsLeft > 0);
}

void Monopoly::Gamestate::inputExecutor(int userChoice) {

  if (userChoice == -1 && currentPlayer->InJail()) {
    currentPlayer->TakeMoney(currentPlayer->GetBailAmount());
    currentPlayer->LeaveJail();
    userChoice = getUserTurn(currentPlayer->GetName());
  }
  int roll, roll1, roll2;
  playerTerminatedThisTurn = false;
  //===========================================User Choice 4==========================================================//
  if (userChoice == 4) {
    currentPlayer->TerminatePlayer(*board);
    currentPlayer = GetNextPlayer();
    playerTerminatedThisTurn = true;
    numRollsThisTurn = 0;
  }
    //===========================================User Choice 1 and not in jail=========================================//
  else if (userChoice == 1 && !currentPlayer->InJail()) {
    if (rules->numTurns() != -1) numTurnsLeft--;
    roll1 = dice->GetRoll();
    roll2 = dice->GetRoll();
    roll = roll1 + roll2;
    movePlayer(roll);
    std::cout << currentPlayer->GetName() << ", you rolled a " << roll << std::endl;
    numRollsThisTurn++;
    board->At(currentPlayer->GetCurrentPosition())->activate(*currentPlayer);
    //=========================================User Choice 1 and in jail==============================================//
  } else if (userChoice == 1 && currentPlayer->InJail()){
    roll1 = dice->GetRoll();
    roll2 = dice->GetRoll();
    if(roll1 == roll2){
      std::cout << "You got out of jail by rolling doubles\n";
      currentPlayer->LeaveJail();
    } else {
      std::cout << currentPlayer->GetName() << ", you rolled a " << roll1 + roll2 << "\nYou are still stuck in jail\n";
      currentPlayer->DecrementJailtime(*board, rules->PutMoneyInFP());
      numRollsThisTurn++;
    }
    //==========================================User Choice 2=========================================================//
  } else if (userChoice == 2) {
    auto props = board->GetUpgradableProps(*currentPlayer, rules->BuildHousesEvenly());
    int upgradeChoice = Monopoly::GetPropToUpgrade(props);
    if (upgradeChoice != -1) {
      props[upgradeChoice]->BuyUpgrade();
    }
    //=========================================User Choice 3==========================================================//
  } else if (userChoice == 3) {
    auto props = board->GetDowngradeableProps(*currentPlayer, rules->BuildHousesEvenly());
    int downgradeChoice = Monopoly::GetPropToDowngrade(props);
    if (downgradeChoice != -1) {
      props[downgradeChoice]->SellUpgrade();
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
  board->RemoveLander(currentPlayer);
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
  for(auto &player : players){
    board->At(0)->AddLander(&player);
  }
  Space::Property::boardSpaces = board.get(); // Assigning statics
  Space::Property::rulesList = rules.get();
  Space::Property::playerRoster = &players;
  Space::PayToBank::boardSpaces = board.get();
  Space::PayToBank::rulesList = rules.get();
  Space::GotoJail::boardSpaces = board.get();
}

int Monopoly::Gamestate::UserTurn() {
  if(currentPlayer->InJail() && currentPlayer->TurnsInJail() == 0) currentPlayer->DecrementJailtime(*board, rules->PutMoneyInFP());
  if(!currentPlayer->IsActive()) currentPlayer = GetNextPlayer();
  if(CountActivePlayers() == 1) {
    return -1;
  } else if (currentPlayer->InJail()){
    std::cout << currentPlayer->GetName() << " you are in jail for " << currentPlayer->TurnsInJail() << " turns.\n";
  }
  if(!currentPlayer->InJail() || !currentPlayer->CanAffordBail()) {
    return getUserTurn(currentPlayer->GetName());
  } else {
    return GetJailTurn(currentPlayer->GetName(), currentPlayer->GetBailAmount());
  }
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
  for (int i = 0; i < board->NumProps(); i++) {
    if (board->GetProperty(i)->IsOwned() && board->GetProperty(i)->GetOwner()->GetID() == player.GetID()) {
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


