//
// Created by fidel on 1/31/18.
//

#include "gameStateHandler.h"
Monopoly::Gamestate::Gamestate(char **args) : currentPlayer(nullptr) {
  board = std::make_unique<Monopoly::Board>(args[2]);
  rules = std::make_unique<Monopoly::Rules>(args[1]);
  dice = std::make_unique<Monopoly::DiceRoller>(args[3]);
  numRollsLeft = rules->numTurns();
  currPlayerNum = 0;
  playerTerminatedThisTurn = false;
}

Monopoly::Gamestate::~Gamestate() {

}

bool Monopoly::Gamestate::gameActive() {
  return CountActivePlayers() > rules->numPlayersToEnd() && (numRollsLeft == -1 || numRollsLeft > 0);
}

void Monopoly::Gamestate::inputExecutor(int userChoice) {
  playerTerminatedThisTurn = false;
  auto currProp = board->GetProperty(currentPlayer->GetCurrentPosition());
  auto currSpace = board->GetSpace(currentPlayer->GetCurrentPosition());
  if (userChoice == 2) {
    currentPlayer->TerminatePlayer(*board);
    currentPlayer = GetNextPlayer();
    playerTerminatedThisTurn = true;
  } else if (userChoice == 1) {
    if (rules->numTurns() != -1) numRollsLeft--;
    int roll = dice->GetRoll();
    movePlayer(roll);
    currSpace = board->GetSpace(currentPlayer->GetCurrentPosition());
    currProp = board->GetProperty(currentPlayer->GetCurrentPosition());
    std::cout << currentPlayer->GetName() << ", you rolled a " << roll << std::endl;
    if (currSpace->GetType() == SpaceType::Property
        && currProp->IsOwned() && currProp->GetOwner()->GetID() != currentPlayer->GetID()) {
      landedOnOtherPlayersSpace();
    } else if (currSpace->GetType() == SpaceType::Property && !currSpace->IsOwned()) {
      landedOnUnownedSpace();
    } else if (currSpace->IsOwned() && currSpace->GetOwner()->GetID() == currentPlayer->GetID()) {
      std::cout << currentPlayer->GetName() << ", you landed on " << currSpace->GetName() << "which you already own\n";
    }
  }
  if (!playerTerminatedThisTurn) currentPlayer = GetNextPlayer();
}

void Monopoly::Gamestate::landedOnOtherPlayersSpace() {
  int rent = 0;
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
    currentPlayer = GetNextPlayer();
    playerTerminatedThisTurn = true;
  }
}

void Monopoly::Gamestate::landedOnUnownedSpace() {
  if (board->GetSpace(currentPlayer->GetCurrentPosition())->GetType() == SpaceType::Property &&
      !board->GetProperty(currentPlayer->GetCurrentPosition())->IsOwned()
      && currentPlayer->GetAmountMoney() >= board->GetProperty(currentPlayer->GetCurrentPosition())->GetCost()) {
    //Property is unowned and player has enough money to buy
    if (Monopoly::offerBuy(*currentPlayer, *board->GetProperty(currentPlayer->GetCurrentPosition()))) {
      board->GetProperty(currentPlayer->GetCurrentPosition())->SetOwner(currentPlayer);
      currentPlayer->TakeMoney(board->GetProperty(currentPlayer->GetCurrentPosition())->GetCost());
      std::cout << currentPlayer->GetName() << " bought "
                << board->GetProperty(currentPlayer->GetCurrentPosition())->GetName() << " for $"
                << board->GetProperty(currentPlayer->GetCurrentPosition())->GetCost() << std::endl;
    }
  } else if (!board->GetProperty(currentPlayer->GetCurrentPosition())->IsOwned()
      && currentPlayer->GetAmountMoney() < board->GetProperty(currentPlayer->GetCurrentPosition())->GetCost()) {
    std::cout << currentPlayer->GetName() << ", you don't have enough money to afford "
              << board->GetSpace(currentPlayer->GetCurrentPosition())->GetName() << ".\n";
    std::cout << board->GetSpace(currentPlayer->GetCurrentPosition())->GetName() << " costs $"
              << board->GetProperty(currentPlayer->GetCurrentPosition())->GetCost() << " but you only have $"
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
