//
// Created by mfbut on 3/10/2018.
//

#ifndef MYVECTOR_MYVECTOR_H
#define MYVECTOR_MYVECTOR_H

#include <sstream>
#include <stdexcept>
#include <memory>
#include <algorithm>
#include <vector>
#include <ostream>
#include "ConstVectorItr.h"
#include "VectorItr.h"

//overloaded out for MyVector. Prints {element1 element2 element3 ...}
//you may choose to make this function a friend of MyVector if you want
template<typename T>
std::ostream& operator<<(std::ostream& out, const MyVector<T>& myVector);


template<typename T>
class MyVector {
 public:

  MyVector();
  explicit MyVector(const unsigned int& numElements); //create numElements empty items
  MyVector(const unsigned int& numElements, const T& value); // create numElements items all initialized to value
 
  //here I am templating this particular member method over another type U
  //this will allow us to convert things like a vector<vector<string>> to a 
  //MyVector<MyVector<string>> which wouldn't be possible othewise
  template <typename U>
  MyVector(const std::vector<U>& values); // create a MyVector with the same values as standard vector
  MyVector(const MyVector& orig); // create a copy of a MyVector
  virtual ~MyVector(); //clean up any dynamically allocated space for a MyVector
  MyVector& operator=(const MyVector& rhs); // make this MyVector have a COPY of all the values in rhs

  unsigned int size() const; // return the
  bool isEmpty() const; //return true if the vector has no elements in it

  T& front(); //return a reference the first element in MyVector
  const T& front() const; //return a const reference the first element in MyVector
  T& back(); //return a reference to the last element in MyVector
  const T& back() const; //return a const reference to the last element in MyVector
  T& at(const unsigned int& index); //return a reference to the element at the specified position
  const T& at(const unsigned int& index) const;  //return a const reference to the element at the specified position
  T& operator[](const unsigned int& index); //return a reference to the element at the specified position
  const T& operator[](const unsigned int& index) const; //return a const reference to the element at the specified position

  //insert a value into the vector at the specified position
  //for the iterator versions the position is wherever they are pointing at in the vector
  void insert(const unsigned int& pos, const T& value);
  void insert(const VectorItr<T>& itr, const T& value);
  void insert(const ConstVectorItr<T>& itr, const T& value);

  //remove a value from the vector at the specified position
  //for the iterator versions the position is wherever they are pointing at in the vector
  void erase(const unsigned int& pos);
  void erase(const VectorItr<T>& itr);
  void erase(const ConstVectorItr<T>& itr);

  void pushBack(const T& value); // add an element to the end of the vector
  void popBack(); // remove the last element from the vector

  void clear();// remove all the elements from the vector


  ConstVectorItr<T> begin() const;//get a constant iterator to the beginning of the vector
  ConstVectorItr<T> end() const; //get a constant iterator to the end of the vector

  VectorItr<T> begin(); //get a mutating iterator to the beginning of the vector
  VectorItr<T> end();  //get a mutating iterator to the beginning of the vector

  ConstVectorItr<T> cbegin() const;//get a constant iterator to the beginning of the vector
  ConstVectorItr<T> cend() const; //get a constant iterator to the end of the vector

};



//this is a nested template declaration. 
//this is the right way of doing things if you have a template show up inside another template
//I've given you this because we didn't cover it in class
template<typename T>
template <typename U>
MyVector<T>::MyVector(const std::vector<U>& values) : numContained(values.size()), capacity(values.size()) {

}

#endif //MYVECTOR_MYVECTOR_H
