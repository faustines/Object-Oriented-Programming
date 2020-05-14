//
// Created by mfbut on 3/2/2018.
//

#ifndef MATRIX_MATRIXSIZEERROR_H
#define MATRIX_MATRIXSIZEERROR_H
#include "Matrix.h"
#include "MatrixError.h"

class MatrixSizeError : public MatrixError{
 public:
  MatrixSizeError(std::string &str);
  MatrixSizeError() = default;

  const char *what() const noexcept override;

};

#endif //MATRIX_MATRIXSIZEERROR_H
