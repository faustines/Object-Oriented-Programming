//
// Created by mfbut on 3/11/2018.
//

#ifndef MYVECTOR_CONSTVECTORITR_H
#define MYVECTOR_CONSTVECTORITR_H

template <typename T>
class ConstVectorItr {
  ConstVectorItr& operator++(); //pre
  ConstVectorItr operator++(int); //post

  ConstVectorItr& operator--(); // pre
  ConstVectorItr operator--(int); //post

  ConstVectorItr& operator+=(const unsigned int& rhs); //advance rhs elements
  ConstVectorItr operator+(const unsigned int& rhs); //create a new iterator that is rhs elements beyond the current one

  ConstVectorItr& operator-=(const unsigned int& rhs); //go back rhs elements
  ConstVectorItr operator-(const unsigned int& rhs); // create a new iterator that is rhs elements before the current one

  operator bool() const; // true if pointing to an element within the vector
  bool operator!() const; // true if pointing outside the bounds of the vector
  bool operator==() const; // true if referring to the same vector and (at the same position or out of bounds)
  bool operator!=() const; // opposite of ==

  T& operator*(); //get the element at the current position
  const T& operator*() const; //get the element at the current position
};

#endif //MYVECTOR_CONSTVECTORITR_H
