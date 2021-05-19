// Copyright 2021 Napylov Evgenii
#include <gtest/gtest.h>
#include <iostream>

#include "./contrast.h"

TEST(Linear_stretch_contrast_OMP, Manual_Calc_1) {
    VecImage image = {0, 1, 1, 1, 0, 1 };
    VecImage correct = { 0, 255, 255, 255, 0, 255 };
    VecImage res = add_contrast_omp(image);
    for (size_t i = 0; i < image.size(); i++) {
        ASSERT_EQ(correct[i], res[i]);
    }
}

TEST(Linear_stretch_contrast_OMP, Manual_Calc_2) {
    VecImage image = { 5, 123, 28, 240 };
    VecImage correct = { 0, 128, 25, 255 };
    VecImage res = add_contrast_omp(image);
    for (size_t i = 0; i < image.size(); i++) {
        ASSERT_EQ(correct[i], res[i]);
    }
}

TEST(Linear_stretch_contrast_OMP, Manual_Calc_3) {
    VecImage image = { 57, 120, 99, 32, 17, 64, 1, 55, 200 };
    VecImage correct = { 72, 152, 126, 40, 21, 81, 0, 69, 255 };
    VecImage res = add_contrast_omp(image);
    for (size_t i = 0; i < image.size(); i++) {
        ASSERT_EQ(correct[i], res[i]);
    }
}

TEST(Linear_stretch_contrast_OMP, Manual_Calc_4) {
    VecImage image = { 1, 2, 3, 4, 5, 1 };
    VecImage correct = { 0, 64, 128, 191, 255, 0 };
    VecImage res = add_contrast_omp(image);
    for (size_t i = 0; i < image.size(); i++) {
        ASSERT_EQ(correct[i], res[i]);
    }
}

TEST(Linear_stretch_contrast_OMP, Seq_vs_Omp) {
    double t1, t2, dt_seq, dt_omp;
    VecImage image = RandomVector(200 * 400);

    t1 = omp_get_wtime();
    VecImage res_seq = add_contrast(image);
    t2 = omp_get_wtime();
    dt_seq = t2 - t1;

    t1 = omp_get_wtime();
    VecImage res_omp = add_contrast_omp(image);
    t2 = omp_get_wtime();
    dt_omp = t2 - t1;

    for (size_t i = 0; i < image.size(); i++) {
        ASSERT_EQ(res_seq[i], res_omp[i]);
    }

    std::cout << "seq t: " << dt_seq << "\nomp t: " << dt_omp << std::endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
