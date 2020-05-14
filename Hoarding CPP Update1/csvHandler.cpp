//
// Created by fidel on 1/8/18.
//

#include "csvHandler.h"

std::string getNextCsv(std::ifstream &file) {
  std::string retVal;
  char testVal = 0;
  while (file.good() && testVal != ',' && testVal != '\n') {
    testVal = static_cast<char>(file.get());
    if (testVal != ',' && testVal != '\n') {
      retVal.push_back(testVal);
    }
  }
  return retVal;
}

void skipToTerm(const std::string str, std::ifstream &file) {
  while (file.good()) {
    if (str == getNextCsv(file)) {
      break;
    }
  }
}