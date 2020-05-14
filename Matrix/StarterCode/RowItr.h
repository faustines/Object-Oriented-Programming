//
// Created by mfbut on 3/1/2018.
//

#ifndef MATRIX_ROWITR_H
#define MATRIX_ROWITR_H

#include "Matrix.h"
#include "RowElementItr.h"

class RowItr {
  friend RowElementItr;
 public:

  RowElementItr operator*(); // get iterator over this row

  //advance to next row
  RowItr& operator++(); // pre
  RowItr& operator++(int); // post

  //move to prior row
  RowItr& operator--(); // pre
  RowItr& operator--(int); // post

  RowItr& operator+=(const int& rhs); //advance self rhs rows
  RowItr operator+(const int& rhs); //new iterator rhs rows past self

  RowItr& operator-=(const int& rhs); //move self back rhs rows
  RowItr operator-(const int& rhs); //new iterator rhs rows before self

  operator bool() const; //return true if iterator in bounds
  bool operator!() const; //return true if iterator out of bounds
  bool operator==(const RowItr& rhs) const; //referring to same matrix and (at same position or out of bounds)
  bool operator!=(const RowItr& rhs) const; // opposite of ==
  bool operator<(const RowItr& rhs) const; // referring to same matrix and before rhs
  bool operator>(const RowItr& rhs) const; // referring to same matrix and after rhs
  bool operator<=(const RowItr& rhs) const;
  bool operator>=(const RowItr& rhs) const;


  double& operator[](int i); //get the ith element on this row


};

#endif //MATRIX_ROWITR_H
