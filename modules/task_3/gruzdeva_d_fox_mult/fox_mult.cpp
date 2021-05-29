// Copyright 2021 Gruzdeva Diana

#define NOMINMAX

#include "../../../modules/task_3/gruzdeva_d_fox_mult/fox_mult.h"
#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>
#include <random>
#include <algorithm>
#include <vector>

std::vector<double> getRandomMatrix(int size, time_t seed) {
  std::vector<double> matrix(size * size);
  std::mt19937 gen((unsigned int)seed);
  std::uniform_real_distribution<double> dis(-10, 10);

  for (int i = 0; i < size * size; i++) {
    matrix[i] = dis(gen);
  }

  return matrix;
}

std::vector<double> directMultiplication(std::vector<double> matrixA,
                    std::vector<double> matrixB) {
  if (matrixA.size() != matrixB.size()) {
    throw "Matrices sizes differ";
  }

  int size = static_cast<int>(sqrt(matrixA.size()));
  std::vector<double> matrixC(size * size);

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      matrixC[i * size + j] = 0;
      for (int k = 0; k < size; k++) {
        matrixC[i * size + j] += matrixA[i * size + k]
        * matrixB[k * size + j];
      }
    }
  }

  return matrixC;
}

std::vector<double> sequentialFoxMultiplication(std::vector<double> matrixA,
                    std::vector<double> matrixB, int blockSize) {
  if (blockSize == 0) {
    throw "Block size cannot be zero";
  }

  if (blockSize < 0) {
    throw "Block size cannot be negative";
  }

  if (matrixA.size() < (unsigned int)(blockSize * blockSize)) {
    throw "Block size cannot be larger than size of original matrices";
  }

  if (matrixA.size() != matrixB.size()) {
    throw "Matrice's sizes differ";
  }

  if (static_cast<int>(sqrt(matrixA.size())) % blockSize != 0) {
    throw "Cannot multiply matrices using this block size";
  }

  int size = static_cast<int>(sqrt(matrixA.size()));
  std::vector<double> matrixC(size * size);
  int blockCount = size / blockSize;

  for (int i = 0; i < size * size; i++) {
    matrixC[i] = 0;
  }

  for (int i = 0; i < size; i += blockCount) {
    for (int j = 0; j < size; j += blockCount) {
      for (int k = 0; k < size; k += blockCount) {
        for (int ii = i; ii < std::min(size, i + blockCount); ii++) {
          for (int jj = j; jj < std::min(size, j + blockCount); jj++) {
            for (int kk = k; kk < std::min(size, k + blockCount); kk++) {
              matrixC[ii * size + jj] += matrixA[ii * size + kk]
              * matrixB[kk * size + jj];
            }
          }
        }
      }
    }
  }
  return matrixC;
}

std::vector<double> parallelFoxMultiplication(std::vector<double> matrixA,
                    std::vector<double> matrixB) {
  if (matrixA.size() != matrixB.size()) {
    throw "Matrice's sizes differ";
  }

  int size = static_cast<int>(sqrt(matrixA.size()));
  std::vector<double> matrixC(size * size);

  tbb::parallel_for(
    tbb::blocked_range2d<int, int>(0, size, 0, size),
    [&](tbb::blocked_range2d<int, int> r) {
        for (int j = r.rows().begin(); j != r.rows().end(); j++) {
                for (int i = r.cols().begin(); i != r.cols().end(); i++) {
                    for (int k = 0; k < size; k++) {
                        matrixC[j * size + i] += matrixA[j * size + k] *
                        matrixB[k * size + i];
                    }
                }
            }
    });
  return matrixC;
}
