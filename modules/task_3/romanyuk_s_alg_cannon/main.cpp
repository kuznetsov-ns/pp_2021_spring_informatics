// Copyright 2021 Romanyuk Sergey
#include <gtest/gtest.h>
#include <tbb/tbb.h>
#include "../../../modules/task_3/romanyuk_s_alg_cannon/cannon.h"

TEST(Cannon_Multiplication, Test1_Create_Matrix) {
    int n = 20;
    std::vector<double> A = genMatrix(n);
    std::vector<double> B(A);
    ASSERT_EQ(A, B);
}

TEST(Cannon_Multiplication, Test2_Different_Size) {
    std::vector<double> A = { 1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4,
                1, 2, 3, 4 };
    std::vector<double> B(1);
    ASSERT_ANY_THROW(SequentinalMultiMatrix(A, B, 4));
}

TEST(Cannon_Multiplication, Test3_multiplication_10_seq_par) {
    std::vector<double> A = genMatrix(10);
    std::vector<double> B = genMatrix(10);
    std::vector<double> C1 = SequentinalMultiMatrix(A, B, 10);
    std::vector<double> C2 = parallelCannonMult(A, B, 10);

    ASSERT_EQ(C1, C2);
}

TEST(Cannon_Multiplication, Test4_multiplication_4_cannon_par) {
    std::vector<double> A = genMatrix(4);
    std::vector<double> B = genMatrix(4);
    std::vector<double> C1 = CannonMultiplication(A, B, 4);
    std::vector<double> C2 = parallelCannonMult(A, B, 4);
    ASSERT_TRUE(DifferenceMatrix(C1, C2));
}

TEST(Cannon_Multiplication, Test5_Cannon_Parall_Multiplication) {
    std::vector<double> A = { 1, 1, 2, 2,
                             0, 1, 1, 2,
                             0, 0, 1, 1,
                             0, 0, 0, 1 };

    std::vector<double> B = { 1, 1, 2, 2,
                             0, 1, 1, 2,
                             0, 0, 1, 1,
                             0, 0, 0, 1 };

    std::vector<double> C = { 1, 2, 5, 8,
                             0, 1, 2, 5,
                             0, 0, 1, 2,
                             0, 0, 0, 1 };

    std::vector<double> MultiMatrix = CannonMultiplication(A, B, 4);
    ASSERT_TRUE(DifferenceMatrix(C, MultiMatrix));
}

TEST(Cannon_Multiplication, Test6_matrix_mult) {
    int n = 1000;
    std::vector<double> A = genMatrix(n);
    std::vector<double> B = genMatrix(n);
    std::pair<tbb::tick_count, tbb::tick_count> time1, time2;
    time1.first = tbb::tick_count::now();
    std::vector<double> C1 = SequentinalMultiMatrix(A, B, n);;
    time1.second = tbb::tick_count::now();
    std::cout << "Sequential " << (time1.second - time1.first).seconds()
        << ' ' << std::endl;
    time2.first = tbb::tick_count::now();
    std::vector<double> C2 = parallelCannonMult(A, B, n);
    time2.second = tbb::tick_count::now();
    std::cout << "Parallel " << (time2.second - time2.first).seconds()
        << ' ' << std::endl;
    ASSERT_TRUE(DifferenceMatrix(C1, C2));
}
