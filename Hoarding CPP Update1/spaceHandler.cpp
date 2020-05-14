//
// Created by fidel on 1/31/18.
//

#include "spaceHandler.h"

std::string Monopoly::Space::GetName() const {
  return this->name;
}

Monopoly::SpaceType Monopoly::Space::GetType() {
  return this->type;
}

void Monopoly::Space::Activate() {
  std::cout << "Something is wrong. Virtual method for derived class not called\n";
}

Monopoly::Space::~Space() = default;

Monopoly::Space::Space() : type(SpaceType::Space) {
  owned = false;
  ownedBy = nullptr;
  //setID = -1;
}

Monopoly::Player* Monopoly::Space::GetOwner() {
  return ownedBy;
}

bool Monopoly::Space::IsOwned() const {
  return owned;
}

void Monopoly::Space::ResetOwner(){
  this->owned = false;
  this->ownedBy = nullptr;
}

void Monopoly::Space::SetOwner(Player *newOwner) {
  owned = true;
  ownedBy = newOwner;
}
