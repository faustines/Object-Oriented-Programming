//
// Created by mfbut on 3/2/2018.
//

#include <stdexcept>
#include <sstream>
#include "ColItr.h"

ColItr::ColItr(Matrix& mat, int start) : mat(mat), lowerBound(0), upperBound(mat.getNumCols()), index(start) {

}

ColElementItr ColItr::operator*() {
  if (*this) {
    return ColElementItr(*this, 0);
  } else {
    std::stringstream errorStream;
    errorStream << "RowElementItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }
}

ColItr& ColItr::operator++() {
  index++;
  return *this;
}

ColItr& ColItr::operator++(int) {
  return ++(*this);
}

ColItr& ColItr::operator--() {
  index--;
  return *this;
}

ColItr& ColItr::operator--(int) {
  return --(*this);
}

ColItr& ColItr::operator+=(const int& rhs) {
  index += rhs;
  return *this;
}

ColItr ColItr::operator+(const int& rhs) {
  ColItr copy(*this);
  copy += rhs;
  return copy;
}

ColItr& ColItr::operator-=(const int& rhs) {
  index -= rhs;
  return *this;
}

ColItr ColItr::operator-(const int& rhs) {
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

bool ColItr::operator==(const ColItr& rhs) const {
  if (!compatible(rhs)) {
    return false;
  } else if (!*this && !rhs) { // two iterators that are out of bounds
    return true; // are considered to be the same
  } else {
    return index == rhs.index;
  }
}

bool ColItr::operator!=(const ColItr& rhs) const {
  return !(*this == rhs);
}

bool ColItr::operator<(const ColItr& rhs) const {
  return compatible(rhs) && index < rhs.index;
}

bool ColItr::operator>(const ColItr& rhs) const {
  return compatible(rhs) && index > rhs.index;
}

bool ColItr::operator<=(const ColItr& rhs) const {
  return *this == rhs || *this < rhs;
}

bool ColItr::operator>=(const ColItr& rhs) const {
  return *this == rhs || *this > rhs;
}

bool ColItr::compatible(const ColItr& other) const {
  return &mat == &other.mat;
}

void ColItr::replace(const std::vector<double>& newValues) {

  if (*this) {
    mat.values.at(index) = newValues;
  } else {
    std::stringstream errorString;
    errorString << "Attempting to write to col " << index << " but matrix only has rows 0 - " << mat.getNumRows()
                << std::endl;
    throw std::range_error(errorString.str());
  }
}

ColElementItr ColItr::begin() {
  return ColElementItr(*this, 0);
}

ColElementItr ColItr::end() {
  return ColElementItr(*this, mat.getNumRows());
}

double& ColItr::operator[](int i) {
  if (*this) {
    ColElementItr cei = ColElementItr(*this, i);
    return *cei;
  } else {
    std::stringstream errorStream;
    errorStream << "ColItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }

}






