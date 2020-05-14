#include "RowElementItr.h"
#include "RowItr.h"

RowElementItr::RowElementItr(RowItr &ri, int start) : ri(ri), index(start), upperBound(ri.mat.getNumCols()),  lowerBound(0) {

}

//get the element in this row we are pointing at
double &RowElementItr::operator*() {
  return ri.mat.superMatty[ri.index][index];
}
RowElementItr &RowElementItr::operator++() {
  index++;
  return *this;
}
RowElementItr &RowElementItr::operator++(int) {
  return ++(*this);
}
RowElementItr &RowElementItr::operator--() {
  index--;
  return *this;
}
RowElementItr &RowElementItr::operator--(int) {
  return  --(*this);
}
RowElementItr &RowElementItr::operator+=(const int &rhs) {
  index += rhs;
  return *this;
}
RowElementItr RowElementItr::operator+(const int &rhs) {
  RowElementItr copy(*this);
  copy += rhs;
  return copy;
}
RowElementItr &RowElementItr::operator-=(const int &rhs) {
  index -= rhs;
  return *this;
}
RowElementItr RowElementItr::operator-(const int &rhs) {
  RowElementItr copy(*this);
  copy -= rhs;
  return copy;
}
RowElementItr::operator bool() const {
  return index >= lowerBound && index < upperBound;
}
bool RowElementItr::operator!() const {
  return !static_cast<bool>(*this);
}
bool RowElementItr::operator==(const RowElementItr &rhs) const {
  if (&rhs.ri != &ri){
    return false;
  } else if (!(*this) && !rhs){
    return true;
  } else {
    return index == rhs.index;
  }
}
bool RowElementItr::operator!=(const RowElementItr &rhs) const {
  return !static_cast<bool>(*this == rhs);
}
bool RowElementItr::operator<(const RowElementItr &rhs) const {
  return compatible(rhs) && index < rhs.index;
}
bool RowElementItr::operator>(const RowElementItr &rhs) const {
  return compatible(rhs) && index > rhs.index;
}
bool RowElementItr::operator<=(const RowElementItr &rhs) const {
  return *this == rhs || *this < rhs;
}
bool RowElementItr::operator>=(const RowElementItr &rhs) const {
  return *this == rhs || *this > rhs;
}

bool RowElementItr::compatible(const RowElementItr& other) const {
  return &ri.mat == &other.ri.mat;
}

