//
// Created by fidel on 1/31/18.
//

#include "space.h"

std::string Monopoly::Space::GetName() const {
  return this->name;
}

Monopoly::SpaceType Monopoly::Space::GetType() {
  return this->type;
}

Monopoly::Space::~Space() = default;

Monopoly::Space::Space() : type(SpaceType::Space) {

}

void Monopoly::Space::AddLander(Player *lander) {
  landedOnBy.push_back(lander);
}