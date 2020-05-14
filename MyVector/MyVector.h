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

template<typename T>
class MyVector;

//overloaded out for MyVector. Prints {element1 element2 element3 ...}
//you may choose to make this function a friend of MyVector if you want
template<typename T>
std::ostream &operator<<(std::ostream &out, const MyVector<T> &myVector) {
  out << '{';
  for (int i = 0; i < static_cast<int>(myVector.size()); i++) {
    out << myVector[i] << " ";
  }
  //if(myVector.size() > 0) out << myVector.back();
  out << '}';
  return out;

}

template<typename T>
class MyVector {
  friend VectorItr<T>;
  friend ConstVectorItr<T>;

 private:
  unsigned int count;
  T **arr;
  void checkRange(const unsigned int pos, bool inclusive = false) const {
    if (pos < 0 || ((pos >= count && !inclusive) || (pos > count && inclusive))) {
      std::stringstream error;
      error << " Out of bounds exception. Attempted to access the vector at " << pos << " but there are only "
            << count << " elements. ";
      throw(std::out_of_range(error.str()));
    }
  }

 public:

  MyVector() {
    arr = nullptr;
    count = 0;
  }
  explicit MyVector(const unsigned int &numElements) {
    count = numElements;
    arr = new T *[numElements];
    for (unsigned int i = 0; i < numElements; i++) {
      arr[i] = new T;
    }
  }
  //create numElements empty items
  MyVector(const unsigned int &numElements, const T &value) {
    count = numElements;
    arr = new T *[numElements];
    for (unsigned int i = 0; i < numElements; i++) {
      arr[i] = new T(value);
    }
  }
  // create numElements items all initialized to value

  //here I am templating this particular member method over another type U
  //this will allow us to convert things like a vector<vector<string>> to a 
  //MyVector<MyVector<string>> which wouldn't be possible otherwise
  template<typename U>
  MyVector(const std::vector<U> &values) { // create a MyVector with the same values as standard vector
    count = static_cast<int>(values.size());
    arr = new T *[count];
    for (unsigned int i = 0; i < count; i++) {
      arr[i] = new T(values[i]);
    }
  }
  MyVector(const MyVector &orig) {
    count = orig.count;
    arr = new T *[count];
    for (unsigned int i = 0; i < count; i++) {
      arr[i] = new T(*(orig.arr[i]));
    }
  }
  // create a copy of a MyVector
  virtual ~MyVector() {
    for (unsigned int i = 0; i < count; i++) {
      delete arr[i];
    }
    if (count > 0) delete[] arr;
    count = 0;
    arr = nullptr;
  }
  //clean up any dynamically allocated space for a MyVector
  MyVector &operator=(const MyVector &rhs) {
    for (unsigned int i = 0; i < count; i++) {
      delete arr[i];
    }
    delete[] arr;
    count = rhs.count;
    arr = new T *[count];
    for (unsigned int i = 0; i < count; i++) {
      arr[i] = new T(rhs.arr[i]);
    }
    return *this;
  }
  // make this MyVector have a COPY of all the values in rhs

  unsigned int size() const {
    return count;
  }
  // return the
  bool isEmpty() const {
    return count == 0;
  }
  //return true if the vector has no elements in it

  T &front() {
    if (count != 0) {
      return *(arr[0]);
    } else {
      std::stringstream error;
      error << " Out of bounds exception. Attempted to access the vector at " << 0 << " but there are only " << count
            << " elements. ";
      throw std::out_of_range(error.str());
    }
  }
  //return a reference the first element in MyVector
  const T &front() const {
    if (count != 0) {
      return *(arr[0]);
    } else {
      std::stringstream error;
      error << " Out of bounds exception. Attempted to access the vector at " << 0 << " but there are only " << count
            << " elements. ";
      throw std::out_of_range(error.str());
    }
  }
  //return a const reference the first element in MyVector
  T &back() {
    if (count != 0) {
      return *(arr[count - 1]);
    } else {
      std::stringstream error;
      error << " Out of bounds exception. Attempted to access the vector at " << count - 1 << " but there are only "
            << count << " elements. ";
      throw std::out_of_range(error.str());
    }
  }
  //return a reference to the last element in MyVector
  const T &back() const {
    if (count != 0) {
      return *(arr[count - 1]);
    } else {
      std::stringstream error;
      error << " Out of bounds exception. Attempted to access the vector at " << count - 1 << " but there are only "
            << count << " elements. ";
      throw std::out_of_range(error.str());
    }
  }
  //return a const reference to the last element in MyVector
  T &at(const unsigned int &index) {
    checkRange(index);
    return *(arr[index]);
  }
  //return a reference to the element at the specified position
  const T &at(const unsigned int &index) const {
    checkRange(index);
    return *(arr[index]);
  }
  //return a const reference to the element at the specified position
  T &operator[](const unsigned int &index) {
    checkRange(index);
    return *(arr[index]);
  }
  //return a reference to the element at the specified position
  const T &operator[](const unsigned int &index) const {
    checkRange(index);
    return *(arr[index]);
  }
  //return a const reference to the element at the specified position

  //insert a value into the vector at the specified position
  //for the iterator versions the position is wherever they are pointing at in the vector
  void insert(const unsigned int &pos, const T &value) {
    checkRange(pos, true);
    T **temp = new T *[count + 1];
    temp[pos] = new T(value);
    for (unsigned int i = 0; i < count + 1; i++) {
      if (i < pos) {
        temp[i] = arr[i];
      } else if (i > pos) {
        temp[i] = arr[i - 1];
      }
    }
    delete[] arr;
    count++;
    arr = temp;
  }
  void insert(const VectorItr<T> &itr, const T &value) {
    insert(static_cast<const unsigned int>(itr.index), value);
  }
  void insert(const ConstVectorItr<T> &itr, const T &value) {
    insert(static_cast<const unsigned int>(itr.index), value);
  }

  //remove a value from the vector at the specified position
  //for the iterator versions the position is wherever they are pointing at in the vector
  void erase(const unsigned int &pos) {
    checkRange(pos);
    T **temp = new T *[count - 1];
    for (unsigned int i = 0; i < count - 1; i++) {
      if (i < pos) {
        temp[i] = arr[i];
      } else if (i >= pos) {
        temp[i] = arr[i + 1];
      }
    }
    delete arr[pos];
    delete[] arr;
    --count;
    arr = temp;
  }
  void erase(const VectorItr<T> &itr) {
    erase(static_cast<const unsigned int>(itr.index));
  }
  void erase(const ConstVectorItr<T> &itr) {
    erase(static_cast<const unsigned int>(itr.index));
  }

  void pushBack(const T &value) {
    T **temp = new T *[count + 1];
    for (unsigned int i = 0; i < count; i++) {
      temp[i] = arr[i];
    }
    delete[] arr;
    temp[count] = new T(value);
    count++;
    arr = temp;
  }
  // add an element to the end of the vector
  void popBack() {
    T **temp = new T *[count - 1];
    for (unsigned int i = 0; i < count - 1; i++) {
      temp[i] = arr[i];
    }
    delete arr[count - 1];
    delete[] arr;
    --count;
    arr = temp;
  }
  // remove the last element from the vector

  void clear() {
    for (unsigned int i = 0; i < count; i++) {
      delete arr[i];
    }
    count = 0;
    delete[] arr;
    arr = nullptr;
  }
// remove all the elements from the vector


  ConstVectorItr<T> begin() const {
    return ConstVectorItr<T>(*this, 0);
  }
//get a constant iterator to the beginning of the vector
  ConstVectorItr<T> end() const {
    return ConstVectorItr<T>(*this, count);
  }
  //get a constant iterator to the end of the vector

  VectorItr<T> begin() {
    return VectorItr<T>(*this, 0);
  }
  //get a mutating iterator to the beginning of the vector
  VectorItr<T> end() {
    return VectorItr<T>(*this, count);
  }
  //get a mutating iterator to the beginning of the vector

  ConstVectorItr<T> cbegin() const {
    return ConstVectorItr<T>(*this, 0);
  }
//get a constant iterator to the beginning of the vector
  ConstVectorItr<T> cend() const {
    return ConstVectorItr<T>(*this, count);
  }
  //get a constant iterator to the end of the vector

};



//this is a nested template declaration. 
//this is the right way of doing things if you have a template show up inside another template
//I've given you this because we didn't cover it in class
//template<typename T>
//template <typename U>
//MyVector<T>::MyVector(const std::vector<U>& values) {
//
//}

#endif //MYVECTOR_MYVECTOR_H
