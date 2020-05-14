#include "MatrixSizeMismatchError.h"
MatrixSizeMismatchError::MatrixSizeMismatchError(std::string &str) {
  errString = str;
}
const char *MatrixSizeMismatchError::what() const noexcept {
  return errString.c_str();
}
