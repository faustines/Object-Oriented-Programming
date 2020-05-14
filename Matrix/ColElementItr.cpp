#include "ColItr.h"

ColElementItr::ColElementItr(ColItr &ci, int start) : ci(ci), index(start), upperBound(ci.mat.getNumRows()), lowerBound(0) {

}
double &ColElementItr::operator*() {
  return ci.mat.superMatty[index][ci.index];
}
ColElementItr &ColElementItr::operator++() {
  index++;
  return *this;
}
ColElementItr &ColElementItr::operator++(int) {
  return ++(*this);
}
ColElementItr &ColElementItr::operator--() {
  index--;
  return *this;
}
ColElementItr &ColElementItr::operator--(int) {
  return  --(*this);
}
ColElementItr &ColElementItr::operator+=(const int &rhs) {
  index += rhs;
  return *this;
}
ColElementItr ColElementItr::operator+(const int &rhs) {
  ColElementItr copy(*this);
  copy += rhs;
  return copy;
}
ColElementItr &ColElementItr::operator-=(const int &rhs) {
  index -= rhs;
  return *this;
}
ColElementItr ColElementItr::operator-(const int &rhs) {
  ColElementItr copy(*this);
  copy -= rhs;
  return copy;
}
ColElementItr::operator bool() const {
  return index >= lowerBound && index < upperBound;
}
bool ColElementItr::operator!() const {
  return !static_cast<bool>(*this);
}
bool ColElementItr::operator==(const ColElementItr &rhs) const {
  if (&rhs.ci != &ci){
    return false;
  } else if (!(*this) && !rhs){
    return true;
  } else {
    return index == rhs.index;
  }
}
bool ColElementItr::operator!=(const ColElementItr &rhs) const {
  return !static_cast<bool>(*this == rhs);
}
bool ColElementItr::operator<(const ColElementItr &rhs) const {
  return compatible(rhs) && index < rhs.index;
}
bool ColElementItr::operator>(const ColElementItr &rhs) const {
  return compatible(rhs) && index > rhs.index;
}
bool ColElementItr::operator<=(const ColElementItr &rhs) const {
  return *this == rhs || *this < rhs;
}
bool ColElementItr::operator>=(const ColElementItr &rhs) const {
  return *this == rhs || *this > rhs;
}
bool ColElementItr::compatible(const ColElementItr& other) const {
  return &ci.mat == &other.ci.mat;
}