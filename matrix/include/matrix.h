#ifndef MATRIX_H
#define MATRIX_H
#include <cmath>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;
enum MatrixType { Identity, Random };

class Matrix {
private:
  int rows;
  int cols;
  float **data;

public:
  Matrix(int rows_, int cols_);
  Matrix(int rows_, int cols_, float val);
  Matrix(int rows_, int cols_, MatrixType m_type);
  /*Copy constructor: to prevent shallow copy*/
  Matrix(const Matrix &m);
  ~Matrix();
  int get_rows() const;
  int get_cols() const;
  void print() const;
  float &access(int r_ind, int c_ind);
  Matrix operator+(const Matrix &m) const;
  Matrix operator-(const Matrix &m) const;
  Matrix operator*(float val) const;
  Matrix operator/(float val) const;
  Matrix operator*(const Matrix &m) const;
  Matrix operator/(const Matrix &m) const;
  bool operator==(const Matrix &m) const;
  bool operator!=(const Matrix &m) const;
  bool isIdentity() const;
  bool isIdempotent() const;
  bool isSquare() const;
  bool isSymmetric() const;
  bool isUpperTriangle() const;
  bool isLowerTriangle() const;
  Matrix transpose() const;
  void fill(float val);
  float minElement() const;
  float maxElement() const;
  float determinant() const;
  string toString() const;
};

#endif
