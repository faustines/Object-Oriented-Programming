//
// Created by mfbut on 12/29/2017.
//

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Utility.h"

int min(int a, int b) {
  return a < b ? a : b;
}
int max(int a, int b) {
  return a > b ? a : b;
}

/**
 * Read a string of any length from a file.
 * @param file
 * @return The next string in the file or NULL if nothing is left
 */
char* read_str(FILE* file) {
  char* line = NULL;
  int num_chars = 0;
  char c;

  fscanf(file, "%c", &c);

  // read leading whitespace characters
  while(!feof(file)){
    if(!isspace(c)){
      break;
    }
    fscanf(file, "%c", &c);
  }

  // have a character so ok to put it is_in_str
  while (!feof(file)) {
    line = (char*) realloc(line, (num_chars + 1) * sizeof(char));
    line[num_chars] = c;
    num_chars++; // one more character

    if (isspace(c)) {  // reached the end of the string
      break;
    }
    fscanf(file, "%c", &c);
  }

  if (line != NULL) { // null terminate the string if we have one
    if (!isspace(line[num_chars - 1])) { // if the file ended but didn't there wasn't a whitespace at the end
      // need to make space for the null character
      line = (char*) realloc(line, (num_chars + 1) * sizeof(char));
      num_chars++;
    }
    line[num_chars - 1] = '\0';
  }

  return line;
}

void lower_string(char* str){
  for (int i = 0; str[i] != '\0'; ++i) {
    str[i] = tolower(str[i]);
  }
}

/**
 * Return true if yes is the only thing left on the line
 * @param file
 * @return
 */
bool get_yes_no_from_file(FILE* file) {
  bool is_yes = false;
  char* line = read_str(file);

  if(line == NULL){
    return false;
  }else{
    lower_string(line);
    is_yes = strcmp("yes", line) == 0;
    free(line);
    return is_yes;
  }
}

/**
 * Read from file until any of the stop characters are reached.
 * The stop character is consumed and is not part of the string returned
 * @param file: the file to read from
 * @param stop_chars: a string specifying the files to stop on
 * @return: NULL if there is nothing left in the file, otherwise the characters coming before the stop characters
 */
char* read_until_stop(FILE* file, const char* stop_chars) {
  char* line = NULL;
  int num_chars = 0;
  char c;

  fscanf(file, "%c", &c);

  while(!feof(file)){
    line = realloc(line, (num_chars + 1) * sizeof(char));
    line[num_chars] = c;
    num_chars++;
    if(is_in_str(c, stop_chars)){
      break;
    }
    fscanf(file, "%c", &c);
  }

  if (line != NULL) { // null terminate the string if we have one
    // if the end of the file was reached before a stop character was encountered
    if (!is_in_str(line[num_chars - 1], stop_chars)) {
      // need to make space for the null character
      line = (char*) realloc(line, (num_chars + 1) * sizeof(char));
      num_chars++;
    }
    line[num_chars - 1] = '\0';
  }


  return line;
}

/**
 * Check if c is in str
 * @param c
 * @param str
 * @return
 */
bool is_in_str(char c, const char* str) {
  for (int i = 0; str[i] != '\0'; ++i) {
    if(c == str[i]){
      return true;
    }
  }
  return false;
}


/**
 * Check if val is in nums
 * @param val
 * @param nums
 * @param len
 * @return
 */
bool is_in_int(const int val, const int* nums, const int len) {
  for (int i = 0; i < len; ++i) {
    if(val == nums[i]){
      return true;
    }
  }
  return false;
}



/**
 * Read a field from a string field from a csv file
 * @param file
 * @return
 */
char* read_str_csv_field(FILE* file) {
  return read_until_stop(file, ",\n");
}

/**
 * Read an integer field from a csv file
 * @param file
 * @return
 */
int read_int_csv_field(FILE* file) {
  int num = -9;
  char* field = read_str_csv_field(file);
  int num_args_read = sscanf(field, "%d", &num);

  if(num_args_read != 1){
    printf("Trouble reading integer field from csv file.\n");
  }
  if(field != NULL){
    free(field);
  }
  return num;
}

void skip_csv_field(FILE* file) {
  char* field = read_str_csv_field(file);
  if(field != NULL){
    free(field);
  }
}


/**
 * read a line from a file
 * @param file
 * @return
 */
char* read_line(FILE* file) {
  return read_until_stop(file, "\n");
}

/**
 * Skip a line in a file
 * @param file
 */
void skip_line(FILE* file) {
  char* line = read_line(file);
  if(line != NULL){
    free(line);
  }
}

/**
 * Get the maximum value in an arry of ints
 * @param ar
 * @param len
 * @return
 */
int max_ar(const int* ar, const int len) {
  int the_max = ar[0];
  for (int i = 1; i < len; ++i) {
    the_max = max(the_max, ar[i]);
  }
  return the_max;
}


