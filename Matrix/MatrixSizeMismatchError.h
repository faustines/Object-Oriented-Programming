//
// Created by mfbut on 3/2/2018.
//

#ifndef MATRIX_MATRIXSIZEMISMATCHERROR_H
#define MATRIX_MATRIXSIZEMISMATCHERROR_H

#include "MatrixError.h"
#include "Matrix.h"
class MatrixSizeMismatchError : public MatrixError {
 public:
  MatrixSizeMismatchError(std::string &str);
  MatrixSizeMismatchError() = default;

  const char *what() const noexcept override;
};

#endif //MATRIX_MATRIXSIZEMISMATCHERROR_H
