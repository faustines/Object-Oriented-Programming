//
// Created by mfbut on 12/29/2017.
//

#ifndef HOARDING_BOARD_H
#define HOARDING_BOARD_H
#include "HoardingTypeDefs.h"
#include "Space.h"
#include "PropertyManager.h"

Board read_board_from_file(char* board_file_name);
void delete_board(Board* board);



#endif //HOARDING_BOARD_H
