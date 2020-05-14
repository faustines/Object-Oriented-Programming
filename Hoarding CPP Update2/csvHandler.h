//
// Created by fidel on 1/8/18.
//

#ifndef HOARDING_CSVHANDLER_H
#define HOARDING_CSVHANDLER_H

#include <string>
#include <fstream>

std::string getNextCsv(std::ifstream &file);

void skipToTerm(std::string str, std::ifstream &file);

#endif //HOARDING_CSVHANDLER_H
