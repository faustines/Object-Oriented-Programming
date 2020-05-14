#include <stdexcept>
#include <sstream>
#include "RowItr.h"

RowItr::RowItr(Matrix& mat, int start) : upperBound(mat.getNumRows()), lowerBound(0), index(start), mat(mat) {

}

RowElementItr RowItr::operator*() {
  if (*this) {
    return RowElementItr(*this, 0);
  } else {
    std::stringstream errorStream;
    errorStream << "RowItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }
}

RowItr& RowItr::operator++() {
  index++;
  return *this;
}

RowItr& RowItr::operator++(int) {
  return ++(*this);
}

RowItr& RowItr::operator--() {
  index--;
  return *this;
}

RowItr& RowItr::operator--(int) {
  return --(*this);
}

RowItr& RowItr::operator+=(const int& rhs) {
  index += rhs;
  return *this;
}

RowItr RowItr::operator+(const int& rhs) {
  RowItr copy(*this);
  copy += rhs;
  return copy;
}

RowItr& RowItr::operator-=(const int& rhs) {
  index -= rhs;
  return *this;
}

RowItr RowItr::operator-(const int& rhs) {
  RowItr copy(*this);
  copy -= rhs;
  return copy;
}

RowItr::operator bool() const {
  return index >= lowerBound && index < upperBound;
}

bool RowItr::operator!() const {
  return !static_cast<bool>(*this);
}

bool RowItr::operator==(const RowItr& rhs) const {
  if (!compatible(rhs)) {
    return false;
  } else if (!*this && !rhs) { // two iterators that are out of bounds
    return true; // are considered to be the same
  } else {
    return index == rhs.index;
  }
}

bool RowItr::operator!=(const RowItr& rhs) const {
  return !(*this == rhs);
}

bool RowItr::operator<(const RowItr& rhs) const {
  return compatible(rhs) && index < rhs.index;
}

bool RowItr::operator>(const RowItr& rhs) const {
  return compatible(rhs) && index > rhs.index;
}

bool RowItr::operator<=(const RowItr& rhs) const {
  return *this == rhs || *this < rhs;
}

bool RowItr::operator>=(const RowItr& rhs) const {
  return *this == rhs || *this > rhs;
}

bool RowItr::compatible(const RowItr& other) const {
  return &mat == &other.mat;
}

RowElementItr RowItr::begin() {
  return RowElementItr(*this, 0);
}

RowElementItr RowItr::end() {
  return RowElementItr(*this, mat.getNumCols());
}

double& RowItr::operator[](int i) {
  if (*this) {
    RowElementItr rei = RowElementItr(*this, i);
    if (rei) {
      return *rei;
    } else {
      std::stringstream errorStream;
      errorStream << "RowElementItr dereferenced out of bounds. Acceptable values 0 -" << mat.getNumCols() - 1
                  << ". Current position: " << i;
      throw std::out_of_range(errorStream.str());
    }
  } else {
    std::stringstream errorStream;
    errorStream << "RowItr dereferenced out of bounds. Acceptable values 0 -" << (upperBound - 1)
                << ". Current position: " << index;
    throw std::out_of_range(errorStream.str());
  }

}






