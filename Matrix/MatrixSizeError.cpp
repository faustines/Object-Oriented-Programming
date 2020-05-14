#include "MatrixSizeError.h"

MatrixSizeError::MatrixSizeError(std::string &str) {
  errString = str;
}
const char *MatrixSizeError::what() const noexcept {
  return errString.c_str();
}
