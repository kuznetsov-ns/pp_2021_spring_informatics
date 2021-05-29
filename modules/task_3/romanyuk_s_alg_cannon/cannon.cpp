// Copyright 2021 Romanyuk Sergey
#include <tbb/tbb.h>
#include "../../../modules/task_3/romanyuk_s_alg_cannon/cannon.h"


std::vector<double> genMatrix(int n) {
    if (n <= 0) {
        throw("Incorrect size!");
    }

    std::vector<double> matrix(n * n);

    std::mt19937 random;
    random.seed(static_cast<unsigned int>(time(0)));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i * n + j] = random() % 100;
        }
    }
    return matrix;
}

std::vector<double> SequentinalMultiMatrix(const std::vector<double>& A,
    const std::vector<double>& B, int n) {

    if (A.size() != B.size()) {
        throw "Matrices sizes differ";
    }

    std::vector<double> res(n * n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                res[i * n + j] += A[i * n + k] * B[k * n + j];
            }
        }
    }
    return res;
}

std::vector<double> CannonMultiplication(std::vector<double> A,
    std::vector<double> B, int n) {

    if (A.size() != B.size()) {
        throw "Size of matrix different";
    }

    if (n <= 0) {
        throw "Size of Block must be > 0";
    }

    if (A.size() < (unsigned int)(n * n)) {
        throw "Block size cannot be larger than size of original matrices";
    }

    int size = static_cast<int>(sqrt(A.size()));
    std::vector<double> C(size * size);

    for (int i = 0; i < size * size; i++) {
        C[i] = 0;
    }

    for (int i = 0; i < size; i += n) {
        for (int j = 0; j < size; j += n) {
            for (int k = 0; k < size; k += n) {
                for (int ii = i; ii < fmin(size, i + n); ii++) {
                    for (int jj = j;
                        jj < fmin(size, j + n); jj++) {
                        for (int kk = k;
                            kk < fmin(size, k + n); kk++) {
                            C[ii * size + jj] += A[ii * size + kk]
                                * B[kk * size + jj];
                        }
                    }
                }
            }
        }
    }
    return C;
}



std::vector<double> parallelCannonMult(const std::vector<double>& A,
    const std::vector<double>& B, int n) {
    if (A.size() != B.size()) {
        throw "Size of matrix different";
    }

    if (n <= 0) {
        throw "Size of Block must be > 0";
    }

    if (A.size() < (unsigned int)(n)) {
        throw "Block size cannot be larger than size of original matrices";
    }


std::vector<double> res(n*n);

tbb::parallel_for(
    tbb::blocked_range2d<int, int>(0, n, 0, n),
    [&](tbb::blocked_range2d<int, int> r) {
        int k1 = r.cols().begin();
        int k2 = r.cols().end();
        int t1 = r.rows().begin();
        int t2 = r.rows().end();
        for (int j = t1; j != t2; j++) {
            for (int i = k1; i != k2; i++) {
                for (int k = 0; k < n; k++) {
                    res[j * n + i] += A[j * n + k] * B[k * n + i];
                }
            }
        }
    });
return res;
}

bool Difference(const double &x, const double &y) {
    return std::fabs(x - y) < 0.001;
}

bool DifferenceMatrix(const std::vector<double>&A,
    const std::vector<double>&B) {
    if (A.size() != B.size())
        throw "Different size of matrix";
    int size = A.size();
    for (int i = 0; i < size; i++)
        if (!Difference(A[i], B[i]))
            return false;
    return true;
}
