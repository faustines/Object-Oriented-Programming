#include "ColItr.h"

ColItr::ColItr(Matrix &mat, int start) : upperBound(mat.getNumCols()), lowerBound(0), index(start), mat(mat) {

}
ColElementItr ColItr::operator*() {
  if (*this) {
    return ColElementItr(*this, 0);
  } else {
    std::stringstream errorStream;
    errorStream << "RowItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }
}
ColItr &ColItr::operator++() {
  index++;
  return *this;
}
ColItr &ColItr::operator++(int) {
  return ++(*this);
}
ColItr &ColItr::operator--() {
  index--;
  return *this;
}
ColItr &ColItr::operator--(int) {
  return --(*this);
}
ColItr &ColItr::operator+=(const int &rhs) {
  index += rhs;
  return *this;
}
ColItr ColItr::operator+(const int &rhs) {
  ColItr copy(*this);
  copy += rhs;
  return copy;
}
ColItr &ColItr::operator-=(const int &rhs) {
  index -= rhs;
  return *this;
}
ColItr ColItr::operator-(const int &rhs) {
  ColItr copy(*this);
  copy -= rhs;
  return copy;
}
ColItr::operator bool() const {
  return index >= lowerBound && index < upperBound;
}
bool ColItr::operator!() const {
  return !static_cast<bool>(*this);
}
bool ColItr::operator==(const ColItr &rhs) const {
  if (!compatible(rhs)) {
    return false;
  } else if (!*this && !rhs) { // two iterators that are out of bounds
    return true; // are considered to be the same
  } else {
    return index == rhs.index;
  }
}
bool ColItr::operator!=(const ColItr &rhs) const {
  return !(*this == rhs);
}
bool ColItr::operator<(const ColItr &rhs) const {
  return compatible(rhs) && index < rhs.index;
}
bool ColItr::operator>(const ColItr &rhs) const {
  return compatible(rhs) && index > rhs.index;
}
bool ColItr::operator<=(const ColItr &rhs) const {
  return *this == rhs || *this < rhs;
}
bool ColItr::operator>=(const ColItr &rhs) const {
  return *this == rhs || *this > rhs;
}
double &ColItr::operator[](int i) {
  if (*this) {
    ColElementItr rei = ColElementItr(*this, i);
    return *rei;
  } else {
    std::stringstream errorStream;
    errorStream << "RowItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }
}
bool ColItr::compatible(const ColItr& other) const {
  return &mat == &other.mat;
}
ColElementItr ColItr::begin() {
  return ColElementItr(*this, 0);
}
ColElementItr ColItr::end() {
  return ColElementItr(*this, mat.getNumRows());
}
