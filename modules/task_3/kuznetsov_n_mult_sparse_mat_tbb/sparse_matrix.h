// Copyright 2021 Kuznetsov Nikita
#ifndef MODULES_TASK_3_KUZNETSOV_N_MULT_SPARSE_MAT_TBB_SPARSE_MATRIX_H_
#define MODULES_TASK_3_KUZNETSOV_N_MULT_SPARSE_MAT_TBB_SPARSE_MATRIX_H_

#include <vector>

class SparseMatrix {
public:
  std::vector<double> values;
  std::vector<int> col_indexes, rows;
  int num_nzero, size;

  SparseMatrix(const std::vector<double>& _values,
    const std::vector<int>& _col_indexes,
    const std::vector<int>& _rows, int _num_nzero, int _size);

  SparseMatrix(int _size, int _num_nzero, unsigned int seed = 475);  // Random
  bool operator==(const SparseMatrix& SM);

  SparseMatrix transpose();
  SparseMatrix ParallelMult(const SparseMatrix& SM, int th);
  SparseMatrix operator*(const SparseMatrix& SM);
};

#endif  // MODULES_TASK_3_KUZNETSOV_N_MULT_SPARSE_MAT_TBB_SPARSE_MATRIX_H_
