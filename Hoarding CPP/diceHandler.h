//
// Created by fidel on 1/10/18.
//

#ifndef HOARDING_RANDOMNUMBERSHANDLER_H
#define HOARDING_RANDOMNUMBERSHANDLER_H

#include <fstream>

namespace Monopoly {

class DiceRoller{
 private:
  std::ifstream file;

 public:
  explicit DiceRoller(char *filename);
  ~DiceRoller();
  int GetRoll();
};
}

#endif //HOARDING_RANDOMNUMBERSHANDLER_H
