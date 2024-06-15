# Matrix-with-cpp
This code was built using C++ programming and provides array functionality.
The functions include:

  1. Building matrices with four constructors:
      A. Initialize all values to zero.
      B. Initialize all values with a specified value.
      C. Build an identity matrix.
      D. Build a random matrix.
  2. get_row() to get the number of rows.
  3. get_col() to get the number of columns.
  4. print() to print the matrix, but not in mathematical form.
  5. access(int r_index, int c_index) to get or set the element at [r_index, c_index].
  6. operator+(Matrix &m) to add matrix m to the current matrix and return the sum.
  7. operator-(Matrix &m) to subtract matrix m from the current matrix and return the difference.
  8. operator*(float val) to multiply the current matrix elements by val and return the result.
  9. operator/(float val) to divide the current matrix elements by val and return the result.
  10. operator*(Matrix &m) to multiply the current matrix by matrix m and return the result.
  11. operator/(Matrix &m) to divide the current matrix by matrix m and return the result.
  12. operator==(Matrix &m) to check if matrix m is equal to the current matrix and return a boolean.
  13. operator!=(Matrix &m) to check if matrix m is not equal to the current matrix and return a boolean.
  14. isIdentity() to check if the current matrix is an identity matrix and return a boolean.
  15. isIdempotent() to check if the current matrix is idempotent (A = A * A) and return a boolean.
  16. isSquare() to check if the current matrix is square and return a boolean.
  17. isSymmetric() to check if the current matrix is symmetrical and return a boolean.
  18. isUpperTriangle() to check if the current matrix is upper triangular and return a boolean.
  19. isLowerTriangle() to check if the current matrix is lower triangular and return a boolean.
  20. transpose() to transpose the current matrix and return the result.
  21. fill(float val) to fill all elements in the current matrix with value val.
  22. minElement() to get the minimum element in the current matrix.
  23. maxElement() to get the maximum element in the current matrix.
  24. determinant() to calculate the determinant of the current matrix.
  25. toString() to return a string representation of the matrix in mathematical form.
