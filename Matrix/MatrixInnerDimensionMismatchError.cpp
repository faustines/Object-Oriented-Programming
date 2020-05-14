#include "MatrixInnerDimensionMismatchError.h"

MatrixInnerDimensionMismatchError::MatrixInnerDimensionMismatchError(std::string &str) {
  errString = str;
}

const char *MatrixInnerDimensionMismatchError::what() const noexcept {
  return errString.c_str();
}
