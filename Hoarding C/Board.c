//
// Created by mfbut on 12/29/2017.
//

#include <string.h>
#include <stdlib.h>
#include "Board.h"
#include "Utility.h"

/**
 * Read the board from the specified file, filling in out_board with the board
 * returning a property manager detailing the property sets
 * @param board_file_name
 * @param out_board
 * @return
 */
Board read_board_from_file(char* board_file_name) {
  Board new_board;
  char* field;
  const int num_blank_lines_and_headers = 4;
  FILE* board_file = fopen(board_file_name, "r");

  if(board_file == NULL){
    printf("Could not open board file.\nEnding Program.\n");
    exit(0);
  }

  skip_csv_field(board_file);
  new_board.num_spaces = read_int_csv_field(board_file);
  new_board.spaces = (Space*)malloc(new_board.num_spaces * sizeof(Space));
  new_board.max_space_name_width = 1;

  // skip the blank lines and headers
  for (int i = 0; i < num_blank_lines_and_headers; ++i) {
    skip_line(board_file);
  }

  // read in the spaces of the board
  for (int i = 0; i < new_board.num_spaces; ++i) {
    field = read_str_csv_field(board_file);
    lower_string(field);
    if(strcmp(field, "go") == 0){ // we have a go space
      new_board.spaces[i] = read_go_space_from_file(board_file);
    } else if(strcmp(field, "property") == 0){ // we have a property space
      new_board.spaces[i] = read_property_space_from_file(board_file);
    } else{
      printf("Error in format of board file when reading space %d.\nEnding Program.\n", i);
      exit(0);
    }
    new_board.max_space_name_width = max(new_board.max_space_name_width, strlen(new_board.spaces[i].property->name));
    free(field);
  }




  fclose(board_file);

  return new_board;
}

void delete_board(Board* board) {
  for (int i = 0; i < board->num_spaces; ++i) {
    delete_space(&board->spaces[i]);
  }
  if(board->spaces != NULL){
    free(board->spaces);
  }
  board->num_spaces = 0;
  board->spaces = NULL;
}


