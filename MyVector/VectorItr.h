//
// Created by mfbut on 3/11/2018.
//

#ifndef MYVECTOR_VECTORITR_H
#define MYVECTOR_VECTORITR_H

#include "MyVector.h"
template <typename T>
class MyVector;

template<typename T>
class VectorItr {
  friend class MyVector<T>;
 private:
  int index;
  int lowerbound;
  int upperbound;
  MyVector<T> &myVector;

 public:
  VectorItr(MyVector<T> &myVector, unsigned int index) : index(index), lowerbound(0), upperbound(myVector.size()), myVector(myVector){

  }
  VectorItr& operator++() {
    index++;
    return *this;
  }
  //pre
  VectorItr operator++(int) {
    return ++(*this);
  }
  //post

  VectorItr& operator--() {
    index--;
    return *this;
  }
  // pre
  VectorItr operator--(int) {
    return --(*this);
  }
  //post

  VectorItr& operator+=(const unsigned int& rhs) {
    index += rhs;
    return *this;
  }
  //advance rhs elements
  VectorItr operator+(const unsigned int& rhs) {
    VectorItr copy(*this);
    copy += rhs;
    return copy;
  }
  //create a new iterator that is rhs elements beyond the current one

  VectorItr& operator-=(const unsigned int& rhs) {
    index -= rhs;
    return *this;
  }
  //go back rhs elements
  VectorItr operator-(const unsigned int& rhs) {
    VectorItr copy(*this);
    copy -= rhs;
    return copy;
  }
  // create a new iterator that is rhs elements before the current one

  operator bool() const {
    return (index >= lowerbound && index < upperbound);
  }
  // true if pointing to an element within the vector
  bool operator!() const {
    return !(*this);
  }
  // true if pointing outside the bounds of the vector
  bool operator==(const VectorItr& rhs) const {
    return ((&myVector == &rhs.myVector && index == rhs.index) || (*this == false && rhs == false));
  }
  // true if referring to the same vector and (at the same position or out of bounds)
  bool operator!=(const VectorItr& rhs) const {
    return !(*this == rhs);
  }
  // opposite of ==

  T& operator*() {
    return myVector.at(index);
  }
  //get the element at the current position
  const T& operator*() const {
    try {
      return myVector.at(index);
    } catch (std::out_of_range &e){
      throw (e);
    }
  }
  //get the element at the current position

};

#endif //MYVECTOR_VECTORITR_H
