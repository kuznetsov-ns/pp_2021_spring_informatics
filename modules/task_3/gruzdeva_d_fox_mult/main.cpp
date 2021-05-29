// Copyright 2021 Gruzdeva Diana

#include <gtest/gtest.h>

#include <tbb/tick_count.h>
#include <random>
#include <vector>
#include <iostream>

#include "../../../modules/task_3/gruzdeva_d_fox_mult/fox_mult.h"

TEST(Fox_Multiplication_OMP, DIRECT_AND_FOX_1) {
    std::vector<double> A = getRandomMatrix(100, time(0));

    std::vector<double> B = getRandomMatrix(100, time(0) + 1);

    std::vector<double> C1 = directMultiplication(A, B);

    std::vector<double> C2 = sequentialFoxMultiplication(A, B, 4);

    ASSERT_EQ(C1, C2);
}

TEST(Fox_Multiplication_OMP, DIRECT_AND_FOX_2) {
    std::vector<double> A = getRandomMatrix(100, time(0));

    std::vector<double> B = getRandomMatrix(100, time(0) + 1);

    std::vector<double> C1 = directMultiplication(A, B);

    std::vector<double> C2 = sequentialFoxMultiplication(A, B, 25);

    ASSERT_EQ(C1, C2);
}

TEST(Fox_Multiplication_OMP, DIRECT_AND_PARALL_FOX_1) {
    std::vector<double> A = getRandomMatrix(100, time(0));

    std::vector<double> B = getRandomMatrix(100, time(0) + 1);

    std::vector<double> C1 = directMultiplication(A, B);

    std::vector<double> C2 = parallelFoxMultiplication(A, B);

    ASSERT_EQ(C1, C2);
}

TEST(Fox_Multiplication_OMP, DIRECT_AND_PARALL_FOX_2) {
    std::vector<double> A = getRandomMatrix(250, time(0));

    std::vector<double> B = getRandomMatrix(250, time(0) + 1);

    std::vector<double> C1 = directMultiplication(A, B);

    std::vector<double> C2 = parallelFoxMultiplication(A, B);

    ASSERT_EQ(C1, C2);
}

TEST(Fox_Multiplication_OMP, SEQ_FOX_AND_PAR_FOX_1) {
    std::vector<double> A = getRandomMatrix(100, time(0));

    std::vector<double> B = getRandomMatrix(100, time(0) + 1);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::vector<double> C1 = sequentialFoxMultiplication(A, B, 25);
    tbb::tick_count t2 = tbb::tick_count::now();
    std::cout << "Direct: " << (t2-t1).seconds() << "\n";
    t1 = tbb::tick_count::now();
    std::vector<double> C2 = parallelFoxMultiplication(A, B);
    t2 = tbb::tick_count::now();
    std::cout << "TBB: " << (t2-t1).seconds()  << "\n";

    ASSERT_EQ(C1, C2);
}

TEST(Fox_Multiplication_OMP, SEQ_FOX_AND_PAR_FOX_2) {
    std::vector<double> A = getRandomMatrix(100, time(0));

    std::vector<double> B = getRandomMatrix(100, time(0) + 1);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::vector<double> C1 = sequentialFoxMultiplication(A, B, 4);
    tbb::tick_count t2 = tbb::tick_count::now();
    std::cout << "Direct: " << (t2-t1).seconds() << "\n";
    t1 = tbb::tick_count::now();
    std::vector<double> C2 = parallelFoxMultiplication(A, B);
    t2 = tbb::tick_count::now();
    std::cout << "TBB: " << (t2-t1).seconds()  << "\n";

    ASSERT_EQ(C1, C2);
}

TEST(Fox_Multiplication_OMP, SEQ_FOX_AND_PAR_FOX_3) {
    std::vector<double> A = getRandomMatrix(500, time(0));

    std::vector<double> B = getRandomMatrix(500, time(0) + 1);
    tbb::tick_count t1 = tbb::tick_count::now();
    std::vector<double> C1 = sequentialFoxMultiplication(A, B, 4);
    tbb::tick_count t2 = tbb::tick_count::now();
    std::cout << "Direct: " << (t2-t1).seconds()  << "\n";
    t1 = tbb::tick_count::now();
    std::vector<double> C2 = parallelFoxMultiplication(A, B);
    t2 = tbb::tick_count::now();
    std::cout << "TBB: " << (t2-t1).seconds() << "\n";

    ASSERT_EQ(C1, C2);
}

TEST(Fox_Multiplication_OMP, THROW_DIFFERENT_MATRICES_SIZES) {
    std::vector<double> A = getRandomMatrix(4, time(0));

    std::vector<double> B = getRandomMatrix(5, time(0) + 1);

    ASSERT_ANY_THROW(parallelFoxMultiplication(A, B));
}
