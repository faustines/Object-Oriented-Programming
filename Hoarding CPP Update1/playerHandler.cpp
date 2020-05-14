//
// Created by fidel on 1/31/18.
//
#include "playerHandler.h"

int Monopoly::Player::numPlayers = 0;
Monopoly::Player::Player(std::string NAME, int startingCash) {

  this->id = Monopoly::Player::numPlayers;
  this->active = true;
  this->name = std::move(NAME);
  this->monies = startingCash;
  this->currentPos = 0;
  Monopoly::Player::numPlayers++;
}

void Monopoly::Player::TerminatePlayer(Player &winner, Board &board) {
  board.TransferProperties(winner, this->GetID());
  this->active = false;
  //winner.PayPlayer(this->monies);
  this->monies = 0;
}

void Monopoly::Player::TerminatePlayer(Board &board) {
  this->active = false;
  this->monies = 0;
  board.ResetDanglingSpaces(*this);
}

void Monopoly::Player::PayPlayer(int amount) {
  this->monies += amount;
}

bool Monopoly::Player::TakeMoney(int amount) {
  if (amount > this->monies) {
    return false;
  } else {
    this->monies -= amount;
    return true;
  }
}

bool Monopoly::Player::PayPlayer(int amount, Player &payer, Board &board) {
  if (payer.TakeMoney(amount)) {
    this->PayPlayer(amount);
    return true;
  } else {
    std::cout << payer.GetName() << " went bankrupt to " << this->name << " for landing on "
              << board.GetProperty(payer.GetCurrentPosition())->GetName() << std::endl;
    this->PayPlayer(payer.GetAmountMoney());
    return false;
  }
}

int Monopoly::Player::GetAmountMoney() const {
  return this->monies;
}

std::string Monopoly::Player::GetName() const {
  return this->name;
}

int Monopoly::Player::GetCurrentPos() const {
  return currentPos;
}

int Monopoly::Player::GetID() const {
  return id;
}

bool Monopoly::Player::IsActive() const {
  return active;
}

int Monopoly::Player::GetCurrentPosition() const {
  return currentPos;
}

void Monopoly::Player::SetCurrentPosition(int pos) {
  this->currentPos = static_cast<unsigned int>(pos);
}

void Monopoly::Player::PrintStats() const {
  std::cout << "[" << this->name << " : $" << this->monies << "]";
}