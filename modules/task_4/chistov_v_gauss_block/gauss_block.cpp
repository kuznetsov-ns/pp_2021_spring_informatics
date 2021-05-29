// Copyright 2021 Chistov Vladimir

#define _USE_MATH_DEFINES

#include "../../../modules/task_4/chistov_v_gauss_block/gauss_block.h"
#include "../../../3rdparty/unapproved/unapproved.h"

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

    const int nthreads = std::thread::hardware_concurrency();
    std::thread* threads = new std::thread[nthreads];

    int blockSideNum = static_cast<int>(std::sqrt(nthreads));
    int blockHeight = height / blockSideNum + height % blockSideNum;
    int blockWidth = width / blockSideNum + width % blockSideNum;

    for (int i = 0; i < nthreads; i++) {
        threads[i] = std::thread([&](int thread) {
            int x1 = (thread % blockSideNum) * blockWidth + 1;
            int x2 = std::min(x1 + blockWidth, width - 1);
            int y1 = (thread / blockSideNum) * blockHeight + 1;
            int y2 = std::min(y1 + blockHeight, height - 1);
            for (int x = x1; x < x2; x++) {
                for (int y = y1; y < y2; y++) {
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
        }, i);
    }

    for (int i = 0; i < nthreads; i++) {
        threads[i].join();
    }
    delete[] threads;

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
