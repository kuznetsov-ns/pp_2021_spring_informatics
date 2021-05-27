// Copyright 2021 Kuznetsov Nikita
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include <random>
#include <ctime>
#include <cmath>
#include "../../modules/task_3/kuznetsov_n_mult_sparse_mat_tbb/sparse_matrix.h"

TEST(SPARSE_MATRIX, MAT_EQUAL_ITSELF_1) {
  std::vector<double> arg1 = { 1, 1, 1 };
  std::vector<int> arg2 = { 0, 1, 2, 3 };
  std::vector<int> arg3 = { 0, 1, 2 };
  SparseMatrix A(arg1, arg2, arg3, 3, 3);
  ASSERT_TRUE(A == A);
}

TEST(SPARSE_MATRIX, MAT_EQUAL_ITSELF_2) {
  std::vector<double> arg1 = { 5, 8, 1, 2, 6 };
  std::vector<int> arg2 = { 0, 2, 3, 5, 5 };
  std::vector<int> arg3 = { 0, 3, 2, 1, 3 };
  SparseMatrix A(arg1, arg2, arg3, 5, 4);
  ASSERT_TRUE(A == A);
}

TEST(SPARSE_MATRIX, NO_THROW_WHEN_TRANSPOSE) {
  std::vector<double> arg1 = { 1, 7, 1, 2, 6 };
  std::vector<int> arg2 = { 0, 2, 3, 5, 5 };
  std::vector<int> arg3 = { 0, 3, 2, 1, 3 };
  SparseMatrix A = SparseMatrix(arg1, arg2, arg3, 5, 4);
  ASSERT_NO_THROW(A.transpose());
}

TEST(SPARSE_MATRIX, NO_THROW_WHEN_CREATE_RANDOM_MAT) {
  ASSERT_NO_THROW(SparseMatrix(1, 1, 475));
}

TEST(SPARSE_MATRIX, THROW_WHEN_SIZE_IS_NEGATIVE) {
  ASSERT_ANY_THROW(SparseMatrix(-1, 1, 475));
}

TEST(SPARSE_MATRIX, CORRECT_MULT_IDENTITY_MATRIX) {
  SparseMatrix A({ 1, 1, 1 }, { 0, 1, 2, 3 }, { 0, 1, 2 }, 3, 3);
  SparseMatrix B({ 3, 5, 1 }, { 0, 1, 2, 3 }, { 0, 1, 2 }, 3, 3);
  ASSERT_TRUE(B == A * B);
}

TEST(SPARSE_MATRIX, CORRECT_MULT) {
  SparseMatrix A({ 1, 1 }, { 0, 1, 1, 2 }, { 0, 2 }, 2, 3);
  SparseMatrix B({ 7, 8, 9 }, { 0, 1, 2, 3 }, { 0, 1, 2 }, 3, 3);
  SparseMatrix exp_result({ 7, 9 }, { 0, 1, 1, 2 }, { 0, 2 }, 2, 3);
  SparseMatrix result = A * B;
  ASSERT_TRUE(exp_result == result);
}

TEST(SPARSE_MATRIX, MAT_EQUAL_WITH_SAME_SEED) {
  SparseMatrix A(17, 8, 35);
  SparseMatrix B(17, 8, 35);
  ASSERT_TRUE(A == B);
}

TEST(SPARSE_MATRIX, NO_THROW_WHEN_MULTIPLY) {
  SparseMatrix A(1000, 50, 10);
  SparseMatrix B(1000, 50, 10);
  ASSERT_NO_THROW(A * B);
}

TEST(SPARSE_MATRIX, NO_THROW_WHEN_MULTIPLY_2) {
  SparseMatrix A = SparseMatrix(2000, 500, 475);
  SparseMatrix B = SparseMatrix(2000, 500, 475);
  ASSERT_NO_THROW(A * B);
}

TEST(SPARSE_MATRIX, PARALLEL_MULT_MATRIX_COMPARE_SEQ_1000_ELEM) {
  SparseMatrix A(1000, 100, 10);
  SparseMatrix B(1000, 100, 10);

  auto time1 = tbb::tick_count::now();
  SparseMatrix result = A * B;
  std::cout << "SEQ TIME: " << (tbb::tick_count::now() - time1).seconds() << std::endl;

  time1 = tbb::tick_count::now();
  SparseMatrix par_result = A.ParallelMult(B, 4);
  std::cout << "PAR TIME: " << (tbb::tick_count::now() - time1).seconds() << std::endl;

  bool f = true;
  for (size_t i = 0; i < result.values.size(); i++) {
    if (fabs(result.values[i] - par_result.values[i]) >=
      std::numeric_limits<double>::epsilon()) {
      f = false;
      break;
    }
  }

  ASSERT_TRUE(f);
}

TEST(SPARSE_MATRIX, PARALLEL_MULT_MATRIX_COMPARE_SEQ_2000_ELEM) {
  SparseMatrix A(2000, 200, 10);
  SparseMatrix B(2000, 200, 10);

  auto time1 = tbb::tick_count::now();
  SparseMatrix result = A * B;
  std::cout << "SEQ TIME: " << (tbb::tick_count::now() - time1).seconds() << std::endl;

  time1 = tbb::tick_count::now();
  SparseMatrix par_result = A.ParallelMult(B, 4);
  std::cout << "PAR TIME: " << (tbb::tick_count::now() - time1).seconds() << std::endl;

  bool f = true;
  for (size_t i = 0; i < result.values.size(); i++) {
    if (fabs(result.values[i] - par_result.values[i]) >=
      std::numeric_limits<double>::epsilon()) {
      f = false;
      break;
    }
  }

  ASSERT_TRUE(f);
}

TEST(SPARSE_MATRIX, PARALLEL_MULT_MATRIX_COMPARE_SEQ_4000_ELEM) {
  SparseMatrix A(4000, 300, 10);
  SparseMatrix B(4000, 300, 10);

  auto time1 = tbb::tick_count::now();
  SparseMatrix result = A * B;
  std::cout << "SEQ TIME: " << (tbb::tick_count::now() - time1).seconds() << std::endl;

  time1 = tbb::tick_count::now();
  SparseMatrix par_result = A.ParallelMult(B, 4);
  std::cout << "PAR TIME: " << (tbb::tick_count::now() - time1).seconds() << std::endl;

  bool f = true;
  for (size_t i = 0; i < result.values.size(); i++) {
    if (fabs(result.values[i] - par_result.values[i]) >=
      std::numeric_limits<double>::epsilon()) {
      f = false;
      break;
    }
  }

  ASSERT_TRUE(f);
}

int main(int argc, char** argv) {
    tbb::task_scheduler_init init(tbb::task_scheduler_init::automatic);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
