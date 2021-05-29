// Copyright 2021 Chistov Vladimir

#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include <ctime>
#include "../../../modules/task_4/chistov_v_gauss_block/gauss_block.h"

TEST(Parallel_Count_Sentences_STD, Image10x10) {
    int n = 10;
    std::vector<double> mas(n * n), res(n * n), res1(n * n);
    mas = GenRandVec(n * n);

    double time1 = clock();
    res = Gauss_Sequential(mas, n, n);
    double time2 = clock();
    std::cout << "Sequential time: " << (time2 - time1) / 1000 << std::endl;

    double time3 = clock();
    res1 = Gauss_Parallel(mas, n, n);
    double time4 = clock();
    std::cout << "Parallel time: " << (time4 - time3) / 1000 << std::endl;

    for (int i = 0; i < n*n; i++) {
        std::cout << "res[" << i << "] = " << res[i] << std::endl;
    }
    for (int i = 0; i < n * n; i++) {
        std::cout << "res1[" << i << "] = " << res1[i] << std::endl;
    }
    ASSERT_EQ(res, res1);
}

TEST(Parallel_Count_Sentences_STD, Image1920x1080) {
    int m = 1920;

    int n = 1080;
    std::vector<double> mas(n * m), res(n * m), res1(n * m);
    mas = GenRandVec(n * m);

    double time1 = clock();
    res = Gauss_Sequential(mas, n, m);
    double time2 = clock();
    std::cout << "Sequential time: " << (time2 - time1) / 1000 << std::endl;

    double time3 = clock();
    res1 = Gauss_Parallel(mas, n, m);
    double time4 = clock();
    std::cout << "Parallel time: " << (time4 - time3) / 1000 << std::endl;

    ASSERT_NO_THROW();
}

TEST(Parallel_Count_Sentences_STD, Image2000x2000) {
    int n = 2000;
    std::vector<double> mas(n * n), res(n * n), res1(n * n), res2(n * n);
    mas = GenRandVec(n * n);

    double time1 = clock();
    res = Gauss_Sequential(mas, n, n);
    double time2 = clock();
    std::cout << "Sequential time: " << (time2 - time1) / 1000 << std::endl;

    double time3 = clock();
    res1 = Gauss_Parallel(mas, n, n);
    double time4 = clock();
    std::cout << "Parallel time: " << (time4 - time3) / 1000 << std::endl;

    ASSERT_NO_THROW();
}

TEST(Parallel_Count_Sentences_STD, Image5000x2500) {
    int m = 2500;
    int n = 5000;
    std::vector<double> mas(m * n), res(m * n), res1(m * n), res2(m * n);
    mas = GenRandVec(m * n);

    double time1 = clock();
    res = Gauss_Sequential(mas, m, n);
    double time2 = clock();
    std::cout << "Sequential time: " << (time2 - time1) / 1000 << std::endl;

    double time3 = clock();
    res1 = Gauss_Parallel(mas, m, n);
    double time4 = clock();
    std::cout << "Parallel time: " << (time4 - time3) / 1000 << std::endl;

    ASSERT_NO_THROW();
}

TEST(Parallel_Count_Sentences_STD, Image1000x1000) {
    int n = 1000;
    std::vector<double> mas(n * n), res(n * n), res1(n * n), res2(n * n);
    mas = GenRandVec(n * n);

    double time1 = clock();
    res = Gauss_Sequential(mas, n, n);
    double time2 = clock();
    std::cout << "Sequential time: " << (time2 - time1) / 1000 << std::endl;

    double time3 = clock();
    res1 = Gauss_Parallel(mas, n, n);
    double time4 = clock();
    std::cout << "Parallel time: " << (time4 - time3) / 1000 << std::endl;

    ASSERT_NO_THROW();
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
