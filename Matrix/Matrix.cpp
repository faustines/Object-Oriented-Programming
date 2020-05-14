#include "Matrix.h"
#include "MatrixSizeError.h"
#include "MatrixSizeMismatchError.h"
#include "MatrixInnerDimensionMismatchError.h"

Matrix::Matrix() {

}

Matrix::Matrix(const std::vector<std::vector<double>> &mat) : superMatty(mat) {
  auto numcols = superMatty[0].size();
  for (const auto &vec : superMatty){
    std::string error;
    std::stringstream errorstream;
    errorstream << "All rows of the matrix should have the same number of elements. Expected rows to contain "
                << numcols << " elements but found row that contained " << vec.size() << " elements.";
    error = errorstream.str();
    if (vec.size() != numcols) throw MatrixSizeError(error);
  }
}
Matrix::Matrix(const double val, const int numRows, const int numCols) {
  superMatty.resize(static_cast<unsigned long>(numRows));
  for (std::vector<double> &normalMattys : superMatty){
    normalMattys.resize(static_cast<unsigned long>(numCols), val);
  }
}
int Matrix::getNumRows() const {
  return static_cast<int>(superMatty.size());
}
int Matrix::getNumCols() const {
  if (superMatty.empty()){
   return 0;
  } else {
    return static_cast<int>(superMatty[0].size());
  }
}
Matrix Matrix::operator-() const {
  return Matrix();
}
Matrix &Matrix::operator+=(const Matrix &rhs) {
  if (this->getNumRows() != rhs.getNumRows() || this->getNumCols() != rhs.getNumCols() ){
    std::stringstream errorstream;
    errorstream << "Matrices must be the same size but Matrix1 is " << getNumRows() << " X " << getNumCols() << " and Matrix2 is " << rhs.getNumRows() << " X " << rhs.getNumCols() <<"\n";
    std::string error(errorstream.str());
    throw MatrixSizeMismatchError(error);
  }
  for (int i = 0; i < rhs.getNumRows(); i++){
    for (int j = 0; j < rhs.getNumCols(); j++){
      superMatty[i][j] += rhs.cat(i, j);
    }
  }
  return *this;
}
Matrix &Matrix::operator+=(const double &rhs) {
  if (superMatty.empty()){
    std::string error("MatrixSizeMismatchError");
    throw MatrixSizeMismatchError(error);
  }
  for (int i = 0; i < this -> getNumRows(); i++){
    for (int j = 0; j < this -> getNumCols(); j++){
      superMatty[i][j] += rhs;
    }
  }
  return *this;
}
Matrix Matrix::operator+(const Matrix &rhs) const {
  Matrix temp(*this);
  temp += rhs;
  return temp;
}
Matrix Matrix::operator+(const double &rhs) const {
  Matrix temp(*this);
  temp += rhs;
  return temp;
}
Matrix operator+(const double lhs, const Matrix &rhs) {
  Matrix temp(rhs);
  temp += lhs;
  return temp;
}
Matrix &Matrix::operator-=(const Matrix &rhs) {
  if (this->getNumRows() != rhs.getNumRows() || this->getNumCols() != rhs.getNumCols() ){
    std::string error("MatrixSizeMismatchError");
    throw MatrixSizeMismatchError(error);
  }
  for (int i = 0; i < rhs.getNumRows(); i++){
    for (int j = 0; j < rhs.getNumCols(); j++){
      superMatty[i][j] -= rhs.cat(i, j);
    }
  }
  return *this;
}
Matrix &Matrix::operator-=(const double &rhs) {
  if (superMatty.empty()){
    std::string error("MatrixSizeMismatchError");
    throw MatrixSizeMismatchError(error);
  }
  for (int i = 0; i < this->getNumRows(); i++){
    for (int j = 0; j < this->getNumCols(); j++){
      superMatty[i][j] -= rhs;
    }
  }
  return *this;
}
Matrix Matrix::operator-(const Matrix &rhs) const {
  Matrix temp(*this);
  temp -= rhs;
  return temp;
}
Matrix Matrix::operator-(const double &rhs) const {
  Matrix temp(*this);
  temp -= rhs;
  return temp;
}
Matrix operator-(const double lhs, const Matrix &rhs) {
  Matrix temp(rhs);
  temp *= -1;
  temp += lhs;
  return temp;
}
Matrix &Matrix::operator*=(const Matrix &rhs) {
  if (this->getNumCols() != rhs.getNumRows()){
    std::stringstream errantstream;
    errantstream << "Inner dimensions do not agree. First matrix has " << getNumCols() << " columns but second matrix has " << getNumRows() << " rows.\n";
    std::string e (errantstream.str());
    throw MatrixInnerDimensionMismatchError(e);
  }
  std::vector<std::vector<double>> tempVec;
  tempVec.resize(this->getNumRows());
  for (std::vector<double> &vec : tempVec){
    vec.resize(rhs.getNumCols());
  }
  for (int i = 0; i < this->getNumRows(); i++) {
    for (int j = 0; j < rhs.getNumCols(); j++) {
      for (int k = 0; k < this->getNumCols(); k++) {
        double r1 = this->cat(i, k);
        double r2 = rhs.cat(k, j);
        tempVec[i][j] += r1 * r2;
      }
    }
  }
  superMatty = tempVec;
  return *this;
}
Matrix &Matrix::operator*=(const double &rhs) {
  if (superMatty.empty()){
    std::string error("MatrixInnerDimensionMismatchError");
    throw MatrixInnerDimensionMismatchError(error);
  }
  for (int i = 0; i < this->getNumRows(); i++){
    for (int j = 0; j < this->getNumCols(); j++){
      superMatty[i][j] *= rhs;
    }
  }
  return *this;
}
Matrix Matrix::operator*(const Matrix &rhs) const {
  Matrix temp(*this);
  temp *= rhs;
  return temp;
}
Matrix Matrix::operator*(const double &rhs) const {
  Matrix temp(*this);
  temp *= rhs;
  return temp;
}
Matrix operator*(const double &lhs, const Matrix &rhs) {
  Matrix temp(rhs);
  temp *= lhs;
  return temp;
}
RowItr Matrix::operator[](int i) {
  return RowItr(*this, i);
}
std::ostream &operator<<(std::ostream &out, Matrix &matrix) {
  for (int i = 0; i < matrix.getNumRows(); i++){
    for (int j = 0; j < matrix.getNumCols(); j++){
      out << matrix.superMatty[i][j] << ' ';
    }
    out << '\n';
  }
  return out;
}
std::istream &operator>>(std::istream &in, Matrix &matrix) {
  int rows, cols, val;
  in >> rows;
  in >> cols;
  matrix.superMatty.resize(rows);
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < cols; j++){
      in >> val;
      matrix.superMatty[i].push_back(val);
    }
    std::string error("MatrixSizeError");
    if(static_cast<int>(matrix.superMatty[i].size()) != cols) throw MatrixSizeError(error);
  }
  return in;
}
RowItr Matrix::rowBegin() {
  return RowItr(*this, 0);
}
RowItr Matrix::rowEnd() {
  return RowItr(*this, this->getNumRows());
}
ColItr Matrix::colBegin() {
  return ColItr(*this, 0);
}
ColItr Matrix::colEnd() {
  return ColItr(*this, this->getNumCols());
}
const double & Matrix::cat(int row, int col) const {
  return superMatty[row][col];
}
