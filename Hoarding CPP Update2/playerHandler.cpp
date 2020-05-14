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
  this->inJail = false;
  this->turnsInJail = 0;
  Monopoly::Player::numPlayers++;
}

void Monopoly::Player::TerminatePlayer(Player &winner, Board &board) {
  board.TransferProperties(winner, this->GetID());
  board.RemoveLander(this);
  this->active = false;
  //winner.PayPlayer(this->monies);
  this->monies = 0;
}

void Monopoly::Player::TerminatePlayer(Board &board) {
  this->active = false;
  this->monies = 0;
  board.RemoveLander(this);
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
              << board.At(payer.GetCurrentPosition())->GetName() << std::endl;
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

bool Monopoly::Player::InJail() const {
  return inJail;
}

void Monopoly::Player::PutInJail(int turns, int bail) {
  bailAmount = bail;
  turnsInJail = turns;
  inJail = true;
}

void Monopoly::Player::LeaveJail() {
  turnsInJail = 0;
  inJail = false;
}

void Monopoly::Player::DecrementJailtime(Monopoly::Board &board, bool payToParking) {
  turnsInJail--;
  if(turnsInJail == -1) {
    if (bailAmount > GetAmountMoney()) {
      board.SellToSurvive(*this, bailAmount);
    }
    if(CanAffordBail()){
      std::cout << name << ", you had to pay $" << bailAmount << " to get out of jail\n";
      TakeMoney(bailAmount);
      LeaveJail();
      if (payToParking) Space::FreeParking::AddToPool(bailAmount);
    } else {
      std::cout << name << " went bankrupt when paying to leave jail\n";
      if (payToParking) Space::FreeParking::AddToPool(monies);
      TerminatePlayer(board);
    }
  }
}

bool Monopoly::Player::CanAffordBail() const {
  return (monies >= bailAmount);
}

int Monopoly::Player::GetBailAmount() const {
  return bailAmount;
}

int Monopoly::Player::TurnsInJail() const {
  return turnsInJail;
}

void Monopoly::Player::Deactivate() {
  active = false;
}