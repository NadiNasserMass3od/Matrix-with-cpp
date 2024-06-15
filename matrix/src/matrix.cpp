#include "matrix.h"
#include <cstdlib>
#include <iomanip>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>

Matrix::Matrix(int rows_, int cols_) {
  *data = new float[rows_];

  // data = new float *[rows_];
  for (int i = 0; i < rows_; i++)
    data[i] = new float[cols_];
  rows = rows_;
  cols = cols_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++)
      data[i][j] = 0;
  }
}
Matrix::Matrix(int rows_, int cols_, float val) {
  data = new float *[rows_];
  for (int i = 0; i < rows_; i++)
    data[i] = new float[cols_];
  rows = rows_;
  cols = cols_;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++)
      data[i][j] = val;
  }
}
Matrix::Matrix(int rows_, int cols_, MatrixType m_type) {
  if (rows_ != cols_ && m_type == Identity) {
    cout << "Error in dimensions.\n";
    return;
  }
  data = new float *[rows_];
  for (int i = 0; i < rows_; i++)
    data[i] = new float[cols_];
  rows = rows_;
  cols = cols_;
  if (m_type == Identity) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++)
        if (i == j)
          data[i][i] = 1;
        else
          data[i][j] = 0;
    }
  } else if (m_type == Random) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++)
        data[i][j] = rand();
    }
  }
}
Matrix::Matrix(const Matrix &m) {
  rows = m.rows;
  cols = m.cols;
  data = new float *[rows];
  for (int i = 0; i < rows; i++)
    data[i] = new float[cols];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
      data[i][j] = m.data[i][j];
  }
}
Matrix::~Matrix() {
  for (int i = 0; i < rows; i++)
    delete data[i];
  delete[] data;
}
int Matrix::get_rows() const { return rows; }
int Matrix::get_cols() const { return cols; }
void Matrix::print() const {
  cout << "This matrix is [" << rows << '*' << cols << "]\n";
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
      cout << data[i][j] << " ";
    cout << endl;
  }
}
float &Matrix::access(int r_ind, int c_ind) {
  return data[r_ind - 1][c_ind - 1];
}
Matrix Matrix::operator+(const Matrix &m) const {
  if (rows == m.rows && cols == m.cols) {
    Matrix temp(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        temp.data[i][j] = data[i][j] + m.data[i][j];
      }
    }
    return temp;
  } else {
    cout << "This Matrices can't Add\n";
    exit(0);
  }
}
Matrix Matrix::operator-(const Matrix &m) const {
  if (rows == m.rows && cols == m.cols) {
    Matrix temp(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        temp.data[i][j] = data[i][j] - m.data[i][j];
      }
    }
    return temp;
  } else {
    cout << "This Matrices can't Sub\n";
    exit(0);
  }
}
Matrix Matrix::operator*(float val) const {
  Matrix temp(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      temp.data[i][j] = data[i][j] * val;
    }
  }
  return temp;
}
Matrix Matrix::operator/(float val) const {
  Matrix temp(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      temp.data[i][j] = data[i][j] / val;
    }
  }
  return temp;
}
Matrix Matrix::operator*(const Matrix &m) const {
  if (cols == m.rows) {
    Matrix temp(rows, m.cols);
    float tempval;
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < m.cols; j++) {
        for (int k = 0; k < cols; k++) {
          temp.data[i][j] += data[i][k] * m.data[k][j];
        }
      }
    }
    return temp;
  } else {
    cout << "Error in dimensions\n";
    exit(0);
  }
}
Matrix Matrix::operator/(const Matrix &m) const {

  // First Soluation
  /*
    Matrix temp = m;
    Matrix tempthis(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        tempthis.data[i][j] = data[i][j];
      }
    }
    float delta = tempthis.determinant();
    cout << delta << endl;
    if (delta == 0 || rows != cols) {
      cout << "Can't Do This!!!\n";
      exit(0);
    }

    if (tempthis.data[0][0] == 0) {
      if (tempthis.data[1][0] == 0) {
        float tem;
        for (int j = 0; j < cols; j++) {
          tem = tempthis.data[0][j];
          tempthis.data[0][j] = tempthis.data[2][j];
          tempthis.data[2][j] = tem;
        }
        for (int j = 0; j < m.cols; j++) {
          tem = temp.data[0][j];
          temp.data[0][j] = temp.data[2][j];
          temp.data[2][j] = tem;
        }
      } else {
        float tem;
        for (int j = 0; j < cols; j++) {
          tem = tempthis.data[0][j];
          tempthis.data[0][j] = tempthis.data[1][j];
          tempthis.data[1][j] = tem;
        }
        for (int j = 0; j < m.cols; j++) {
          tem = temp.data[0][j];
          temp.data[0][j] = temp.data[1][j];
          temp.data[1][j] = tem;
        }
      }
    }

    float val;

    val = tempthis.data[0][0];
    for (int j = 0; j < cols; j++)
      tempthis.data[0][j] = tempthis.data[0][j] / val;
    for (int j = 0; j < m.cols; j++)
      temp.data[0][j] = temp.data[0][j] / val;

    val = tempthis.data[1][0];
    for (int j = 0; j < cols; j++)
      tempthis.data[1][j] = tempthis.data[1][j] - tempthis.data[0][j] * val;
    for (int j = 0; j < m.cols; j++)
      temp.data[1][j] = temp.data[1][j] - temp.data[0][j] * val;

    if (m.rows == 3) {
      val = tempthis.data[2][0];
      for (int j = 0; j < cols; j++)
        tempthis.data[2][j] = tempthis.data[2][j] - tempthis.data[0][j] * val;
      for (int j = 0; j < m.cols; j++)
        temp.data[2][j] = temp.data[2][j] - temp.data[0][j] * val;
      if (tempthis.data[1][1] == 0) {
        float tem;
        for (int j = 1; j < cols; j++) {
          tem = tempthis.data[1][j];
          tempthis.data[1][j] = tempthis.data[2][j];
          tempthis.data[2][j] = tem;
        }
        for (int j = 0; j < m.cols; j++) {
          tem = temp.data[1][j];
          temp.data[1][j] = temp.data[2][j];
          temp.data[2][j] = tem;
        }
      }
    }

    val = tempthis.data[1][1];
    for (int j = 1; j < cols; j++)
      tempthis.data[1][j] = tempthis.data[1][j] / val;
    for (int j = 0; j < m.cols; j++)
      temp.data[1][j] = temp.data[1][j] / val;
    Matrix answ(rows, m.cols);

    if (m.rows == 3) {
      val = tempthis.data[2][1];
      for (int j = 1; j < cols; j++)
        tempthis.data[2][j] = tempthis.data[2][j] - tempthis.data[1][j] * val;
      for (int j = 0; j < m.cols; j++)
        temp.data[2][j] = temp.data[2][j] - temp.data[1][j] * val;

      val = tempthis.data[2][2];
      tempthis.data[2][2] = tempthis.data[2][2] / val;
      for (int j = 0; j < m.cols; j++)
        temp.data[2][j] = temp.data[2][j] / val;
      answ.data[2][0] = temp.data[2][0];
      answ.data[1][0] = temp.data[1][0] - answ.data[2][0] * tempthis.data[1][2];
      answ.data[0][0] = temp.data[0][0] - answ.data[2][0] * tempthis.data[0][2]
    - answ.data[1][0] * tempthis.data[0][1]; } else if (m.rows == 2) {
      answ.data[1][0] = temp.data[1][0];
      answ.data[0][0] = temp.data[0][0] - answ.data[1][0] * tempthis.data[0][1];
    }

    return answ;
    */

  if (m.rows != m.cols && m.rows != cols) {
    cout << "Error in dimensions!!!\n";
    exit(0);
  }
  Matrix phan(rows, cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      phan.data[i][j] = data[i][j];
    }
  }
  Matrix temp = m;
  float delta = temp.determinant();
  if (delta == 0) {
    cout << "Can't Do This!!!\n";
    exit(0);
  }
  if (m.rows == 2) {

    float val = temp.data[0][0];
    temp.data[0][0] = temp.data[1][1];
    temp.data[1][1] = val;

    temp.data[1][0] = -1 * temp.data[1][0];
    temp.data[0][1] = -1 * temp.data[0][1];
    Matrix ans = temp / delta;

    return phan * ans;
  } else if (m.rows == 3) {
    int flag = 1;

    for (int i = 0; i < m.rows; i++) {
      for (int s = 0; s < m.cols; s++) {
        float val, ans = 0;
        int test = i, k = s;
        val = 1;
        for (int j = 0; j < m.cols - 1; j++) {
          test++;
          k += flag;
          if (test == m.rows)
            test = 0;
          if (k == m.rows)
            k = 0;
          if (k == -1)
            k = 2;
          val *= m.data[test][k];
        }
        ans += val;

        test = i, k = s;
        val = 1;
        for (int j = 0; j < m.cols - 1; j++) {
          test++;
          k -= flag;
          if (test == m.rows)
            test = 0;
          if (k == m.rows)
            k = 0;
          if (k == -1)
            k = 2;
          val *= m.data[test][k];
        }
        ans -= val;
        ans = ans * flag;
        temp.data[i][s] = ans;
        flag = flag * -1;
      }
    }

    Matrix ans = temp.transpose() / delta;
    return phan * ans;
  } else {
    cout << "Can't Determine!!!";
    exit(0);
  }
}
bool Matrix::operator==(const Matrix &m) const {
  if (cols != m.cols || rows != m.rows) {
    return false;
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (data[i][j] != m.data[i][j]) {
        return false;
      }
    }
  }
  return true;
}
bool Matrix::operator!=(const Matrix &m) const {
  if (cols != m.cols || rows != m.rows) {
    return true;
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (data[i][j] != m.data[i][j]) {
        return true;
      }
    }
  }
  return false;
}
bool Matrix::isIdentity() const {
  if (rows != cols)
    return false;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == j && data[i][i] != 1)
        return false;
      else if (i != j && data[i][j] != 0)
        return false;
    }
  }
  return true;
}
bool Matrix::isIdempotent() const {
  if (rows != cols) {
    return false;
  }
  Matrix temp = (*this) * (*this);
  return ((*this) == temp) ? true : false;
}
bool Matrix::isSquare() const { return rows == cols; }
bool Matrix::isSymmetric() const {
  if (rows != cols) {
    return false;
  }
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (data[i][j] != data[j][i]) {
        return false;
      }
    }
  }
  return true;
}
bool Matrix::isUpperTriangle() const {
  if (cols != rows)
    return false;
  for (int i = 1; i < rows; i++)
    for (int j = 0; j < i; j++)
      if (data[i][j] != 0)
        return false;

  return true;
}
bool Matrix::isLowerTriangle() const {
  if (cols != rows)
    return false;
  for (int j = 1; j < cols; j++)
    for (int i = 0; i < j; i++)
      if (data[i][j] != 0)
        return false;
  return true;
}
Matrix Matrix::transpose() const {
  Matrix temp(cols, rows);
  for (int i = 0; i < cols; i++) {
    for (int j = 0; j < rows; j++) {
      temp.data[i][j] = data[j][i];
    }
  }
  return temp;
}
void Matrix::fill(float val) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      data[i][j] = val;
    }
  }
}
float Matrix::minElement() const {
  float temp = data[0][0];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (temp > data[i][j])
        temp = data[i][j];
    }
  }
  return temp;
}
float Matrix::maxElement() const {
  float temp = data[0][0];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (temp < data[i][j])
        temp = data[i][j];
    }
  }
  return temp;
}
float Matrix::determinant() const {
  if (rows != cols) {
    cout << "Error in dimensions!!" << endl;
    exit(0);
  }
  float det = 1;
  Matrix tt = *this;
  for (int i = 0; i < rows; i++) {
    if (tt.data[i][i] == 0) {
      for (int j = i + 1; j < rows; j++) {
        if (tt.data[j][i] != 0) {
          for (int c = 0; c < cols; c++) {
            det = -det;
            float temp = tt.data[j][c];
            tt.data[j][c] = tt.data[i][c];
            tt.data[i][c] = temp;
          }
          break;
        }
      }
    }
    if (tt.data[i][i] == 0)
      return 0;
    for (int k = i + 1; k < rows; k++) {
      float val = tt.data[k][i] / tt.data[i][i];
      for (int j = i; j < cols; j++) {
        tt.data[k][j] = tt.data[k][j] - val * tt.data[i][j];
      }
    }
  }
  for (int i = 0; i < rows; i++)
    det *= tt.data[i][i];
  return det;


  // if (rows == 3) {
  //   float temp, ans = 0;
  //   for (int j = 0; j < cols; j++) {
  //     temp = 1;
  //     int test = 0, k = j;
  //     temp *= data[test][j];
  //     for (int i = 1; i < rows; i++) {
  //       test++;
  //       k++;
  //       if (k == rows)
  //         k = 0;
  //       temp *= data[test][k];
  //     }
  //     ans += temp;
  //   }
  //   for (int j = 0; j < cols; j++) {
  //     temp = 1;
  //     int test = rows - 1, k = j;
  //     temp *= data[test][j];
  //     for (int i = 1; i < rows; i++) {
  //       test--;
  //       k++;
  //       if (k == rows)
  //         k = 0;
  //       temp *= data[test][k];
  //     }
  //     ans -= temp;
  //   }
  //   return ans;
  // } else
  //   return data[0][0] * data[1][1] - data[0][1] * data[1][0];
}
string Matrix::toString() const {
  int val, step;
  int *count = new int[cols];
  string str = "\xDA";
  for (int j = 0; j < cols; j++) {
    step = 5;
    val = abs(static_cast<int>(data[0][j]));
    for (int i = 1; i < rows; i++) {
      if (val < abs(static_cast<int>(data[i][j])))
        val = abs(static_cast<int>(data[i][j]));
    }
    if (val > 9999999)
      step += 8;
    else if (val > 999999)
      step += 7;
    else if (val > 99999)
      step += 6;
    else if (val > 9999)
      step += 5;
    else if (val > 999)
      step += 4;
    else if (val > 99)
      step += 3;
    else if (val > 9)
      step += 2;
    else
      step++;
    count[j] = step;
    stringstream s;
    s << setw(step) << fixed << setprecision(2) << left << ' ';
    str += s.str();
  }
  str += "\xBF\n";
  for (int i = 0; i < rows; i++) {
    str += "\xB3";
    for (int j = 0; j < cols; j++) {
      stringstream s;
      s << setw(count[j]) << fixed << setprecision(2) << left << data[i][j];
      str += s.str();
    }
    str += "\xB3";
    str += '\n';
  }

  str += "\xC0";
  for (int j = 0; j < cols; j++) {
    stringstream s;
    s << setw(count[j]) << fixed << setprecision(2) << left << ' ';
    str += s.str();
  }
  str += "\xD9";
  str += "\n";
  return string(str);
}
