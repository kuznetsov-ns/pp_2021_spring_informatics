// Copyright 2021 Nikolaev Denis
#include <gtest/gtest.h>
#include <tbb/tick_count.h>
#include "./LinealFiltr.h"

TEST(gaus_filt_Test, invalid_values) {
    int i = 0;
    int j = -2;
    ASSERT_ANY_THROW(createrandmatrix(i, j));
}

TEST(TBB_Gaus_Filter_Test, Test_Matrix_300x100) {
    int i = 300;
    int j = 100;
    double beta = 7;
    int R = 2;
    Matrix imagewGauss(i, std::vector<double>(j));
    Matrix imagewGaussParallel(i, std::vector<double>(j));
    Matrix image(i, std::vector<double>(j));
    Matrix gausskernel = gengausskernel(R, beta);
    image = createrandmatrix(i, j);
    tbb::tick_count start = tbb::tick_count::now();
    imagewGauss = sequentialgaussfilt(image, i, j, R, beta);
    tbb::tick_count end = tbb::tick_count::now();
    std::cout << "Sequential time: " << (end - start).seconds() << std::endl;
    start = tbb::tick_count::now();
    imagewGaussParallel = parallelgaussfilt(image, i, j, R, beta);
    end = tbb::tick_count::now();
    std::cout << "Parallel time: " << (end - start).seconds() << std::endl;
    ASSERT_EQ(imagewGauss, imagewGaussParallel);
}

TEST(TBB_Gaus_Filter_Test, Test_Matrix_500x500) {
    int i = 500;
    int j = 500;
    double beta = 7;
    int R = 2;
    Matrix imagewGauss(i, std::vector<double>(j));
    Matrix imagewGaussParallel(i, std::vector<double>(j));
    Matrix image(i, std::vector<double>(j));
    Matrix gausskernel = gengausskernel(R, beta);
    image = createrandmatrix(i, j);
    tbb::tick_count start = tbb::tick_count::now();
    imagewGauss = sequentialgaussfilt(image, i, j, R, beta);
    tbb::tick_count end = tbb::tick_count::now();
    std::cout << "Sequential time: " << (end - start).seconds() << std::endl;
    start = tbb::tick_count::now();
    imagewGaussParallel = parallelgaussfilt(image, i, j, R, beta);
    end = tbb::tick_count::now();
    std::cout << "Parallel time: " << (end - start).seconds() << std::endl;
    ASSERT_EQ(imagewGauss, imagewGaussParallel);
}
TEST(gaus_filt_Test, matrix_3x3) {
    int i = 3;
    int j = 3;
    double beta = 7;
    int R = 2;
    Matrix imagedef(i, std::vector<double>(j));
    Matrix imagewGauss(i, std::vector<double>(j));
    Matrix imagewGaussParallel(i, std::vector<double>(j));
    Matrix imagecont(i, std::vector<double>(j));
    Matrix gausskernel = gengausskernel(R, beta);
    imagedef[0][0] = 122;
    imagedef[1][0] = 241;
    imagedef[2][0] = 42;
    imagedef[0][1] = 146;
    imagedef[1][1] = 211;
    imagedef[2][1] = 201;
    imagedef[0][2] = 107;
    imagedef[1][2] = 158;
    imagedef[2][2] = 23;

    imagecont[0][0] = 100;
    imagecont[1][0] = 125;
    imagecont[2][0] = 110;
    imagecont[0][1] = 95;
    imagecont[1][1] = 80;
    imagecont[2][1] = 105;
    imagecont[0][2] = 95;
    imagecont[1][2] = 75;
    imagecont[2][2] = 60;

    imagewGauss = sequentialgaussfilt(imagedef, i, j, R, beta);
    imagewGaussParallel = parallelgaussfilt(imagedef, i, j, R, beta);
    // printMatrix(gausskernel, 2 * R + 1, 2 * R + 1);
    // printMatrix(imagedef, i, j);
    // printMatrix(imagewGauss, i, j);
    // printMatrix(imagecont, i, j);
    ASSERT_EQ(imagecont, imagewGauss);
    ASSERT_EQ(imagecont, imagewGaussParallel);
    ASSERT_EQ(imagewGauss, imagewGaussParallel);
}

TEST(TBB_Gaus_Filter_Test, Test_Matrix_400x400) {
    int i = 400;
    int j = 400;
    double beta = 7;
    int R = 2;
    Matrix imagewGauss(i, std::vector<double>(j));
    Matrix imagewGaussParallel(i, std::vector<double>(j));
    Matrix image(i, std::vector<double>(j));
    Matrix gausskernel = gengausskernel(R, beta);
    image = createrandmatrix(i, j);
    tbb::tick_count start = tbb::tick_count::now();
    imagewGauss = sequentialgaussfilt(image, i, j, R, beta);
    tbb::tick_count end = tbb::tick_count::now();
    std::cout << "Sequential time: " << (end - start).seconds() << std::endl;
    start = tbb::tick_count::now();
    imagewGaussParallel = parallelgaussfilt(image, i, j, R, beta);
    end = tbb::tick_count::now();
    std::cout << "Parallel time: " << (end - start).seconds() << std::endl;
    ASSERT_EQ(imagewGauss, imagewGaussParallel);
}


