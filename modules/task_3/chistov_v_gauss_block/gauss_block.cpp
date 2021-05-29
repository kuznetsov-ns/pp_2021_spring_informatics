// Copyright 2021 Chistov Vladimir

#define _USE_MATH_DEFINES

#include "../../../modules/task_3/chistov_v_gauss_block/gauss_block.h"

std::vector<double> Gauss_Sequential(std::vector<double> image, int width,
    int height) {
    std::vector<double> core = Gauss_Core(3);
    std::vector<double> res(width * height);

    for (int x = 1; x < width - 1; x++) {
        for (int y = 1; y < height - 1; y++) {
            double sum = 0;
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    sum += image[height * (x + i) + y + j] *
                        core[3 * (i + 1) + j + 1];
                }
            }
            res[width * x + y] = sum;
           }
       }
    return res;
}

std::vector<double> Gauss_Parallel(std::vector<double> image, int width,
    int height) {
    std::vector<double> core = Gauss_Core(3);
    std::vector<double> res(width * height);
    tbb::task_scheduler_init init;
    tbb::parallel_for(
        tbb::blocked_range2d<int>(1, width -1 , 1, height - 1),
        [&](tbb::blocked_range2d<int> r) {
            for (int x = r.rows().begin(); x != r.rows().end(); ++x) {
                for (int y = r.cols().begin(); y != r.cols().end(); ++y) {
                    double sum = 0;
                    for (int i = -1; i < 2; i++) {
                        for (int j = -1; j < 2; j++) {
                            sum += image[height * (x + i) + y + j] *
                                core[3 * (i + 1) + j + 1];
                        }
                    }
                    res[width * x + y] = sum;
                }
            }
        });

    return res;
}
std::vector<double> GenRandVec(int size) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<double> vec(size);
    for (int i = 0; i < size; i++) {
        vec[i] = gen() % 256;
    }
    return vec;
}

std::vector<double> Gauss_Core(int size, double dev) {
    double sum = 0;
    double s = 2.0 * dev * dev;
    int rad = size / 2;
    std::vector<double> core(size * size);
    for (int i = -rad; i <= rad; i++) {
        for (int j = -rad; j <= rad; j++) {
            double res = (std::exp(-(i * i + j * j) / s)) / (M_PI * s);
            core[size * (i + rad) + j + rad] = res;
            sum += res;
        }
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            core[size * i + j] /= sum;
        }
    }
    return core;
}
