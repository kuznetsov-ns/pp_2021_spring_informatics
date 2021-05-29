// Copyright 2021 Chistov Vladimir

#include<tbb/tick_count.h>
#include <gtest/gtest.h>
#include <vector>
#include <iostream>
#include "../../../modules/task_3/chistov_v_gauss_block/gauss_block.h"

TEST(Parallel_Count_Sentences_TBB, Image10x10) {
    int n = 10;
    std::vector<double> mas(n * n), res(n * n), res1(n * n);
    mas = GenRandVec(n * n);
    tbb::tick_count time1 = tbb::tick_count::now();
    res = Gauss_Sequential(mas, n, n);
    tbb::tick_count time2 = tbb::tick_count::now();
    std::cout << "Sequential time: " << (time2 - time1).seconds() << std::endl;
    tbb::tick_count time3 = tbb::tick_count::now();
    res1 = Gauss_Parallel(mas, n, n);
    tbb::tick_count time4 = tbb::tick_count::now();
    std::cout << "Parallel time: " << (time4 - time3).seconds() << std::endl;
    for (int i = 0; i < n*n; i++) {
        std::cout << "res[" << i << "] = " << res[i] << std::endl;
    }
    for (int i = 0; i < n * n; i++) {
        std::cout << "res1[" << i << "] = " << res1[i] << std::endl;
    }
    ASSERT_NO_THROW();
}

TEST(Parallel_Count_Sentences_TBB, Image1920x1080) {
    int m = 1920;
    int n = 1080;
    std::vector<double> mas(n * m), res(n * m), res1(n * m);
    mas = GenRandVec(n * m);

    tbb::tick_count time1 = tbb::tick_count::now();
    res = Gauss_Sequential(mas, n, m);
    tbb::tick_count time2 = tbb::tick_count::now();
    std::cout << "Sequential time: " << (time2 - time1).seconds() << std::endl;

    tbb::tick_count time3 = tbb::tick_count::now();
    res1 = Gauss_Parallel(mas, n, m);
    tbb::tick_count time4 = tbb::tick_count::now();
    std::cout << "Parallel time: " << (time4 - time3).seconds() << std::endl;

    ASSERT_NO_THROW();
}

TEST(Parallel_Count_Sentences_TBB, Image2000x2000) {
    int n = 2000;
    std::vector<double> mas(n * n), res(n * n), res1(n * n), res2(n * n);
    mas = GenRandVec(n * n);

    tbb::tick_count time1 = tbb::tick_count::now();
    res = Gauss_Sequential(mas, n, n);
    tbb::tick_count time2 = tbb::tick_count::now();
    std::cout << "Sequential time: " << (time2 - time1).seconds() << std::endl;

    tbb::tick_count time3 = tbb::tick_count::now();
    res1 = Gauss_Parallel(mas, n, n);
    tbb::tick_count time4 = tbb::tick_count::now();
    std::cout << "Parallel time: " << (time4 - time3).seconds() << std::endl;

    ASSERT_NO_THROW();
}

TEST(Parallel_Count_Sentences_TBB, Image5000x2500) {
    int m = 2500;
    int n = 5000;
    std::vector<double> mas(m * n), res(m * n), res1(m * n), res2(m * n);
    mas = GenRandVec(m * n);

    tbb::tick_count time1 = tbb::tick_count::now();
    res = Gauss_Sequential(mas, m, n);
    tbb::tick_count time2 = tbb::tick_count::now();
    std::cout << "Sequential time: " << (time2 - time1).seconds() << std::endl;

    tbb::tick_count time3 = tbb::tick_count::now();
    res1 = Gauss_Parallel(mas, m, n);
    tbb::tick_count time4 = tbb::tick_count::now();
    std::cout << "Parallel time: " << (time4 - time3).seconds() << std::endl;

    ASSERT_NO_THROW();
}

TEST(Parallel_Count_Sentences_TBB, Image10000x10000) {
    int n = 10000;
    std::vector<double> mas(n * n), res(n * n), res1(n * n), res2(n * n);
    mas = GenRandVec(n * n);
    tbb::tick_count time1 = tbb::tick_count::now();
    res = Gauss_Sequential(mas, n, n);
    tbb::tick_count time2 = tbb::tick_count::now();
    std::cout << "Sequential time: " << (time2 - time1).seconds() << std::endl;

    tbb::tick_count time3 = tbb::tick_count::now();
    res1 = Gauss_Parallel(mas, n, n);
    tbb::tick_count time4 = tbb::tick_count::now();
    std::cout << "Parallel time: " << (time4 - time3).seconds() << std::endl;

    ASSERT_NO_THROW();
}
