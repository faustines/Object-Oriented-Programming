//
// Created by mfbut on 12/29/2017.
//

#ifndef HOARDING_UTILITY_H
#define HOARDING_UTILITY_H

#include <stdio.h>
#include <stdbool.h>
int min(int a, int b);
int max(int a, int b);
int max_ar(const int* ar, const int len);
char* read_str(FILE* file);
void lower_string(char* str);
bool get_yes_no_from_file(FILE* file);
bool is_in_str(char c, const char* str);
bool is_in_int(const int val, const int* nums, const int len);
char* read_until_stop(FILE* file, const char* stop_chars);
char* read_str_csv_field(FILE* file);
int read_int_csv_field(FILE* file);
void skip_csv_field(FILE* file);
char* read_line(FILE* file);
void skip_line(FILE* file);
#endif //HOARDING_UTILITY_H
