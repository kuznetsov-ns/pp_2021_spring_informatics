// Copyright 2021 Bessolitsyn Sergay

#include <random>

#include "../../../modules/task_3/bessolitsyn_s_quick_sort/quick_sort.h"

std::vector<int> getRandomVector(int size, uint64_t seed) {
    std::vector<int> vec(size);
    std::mt19937 gen;
    gen.seed(seed);
    for (int i = 0; i < size; ++i) {
        vec[i] = gen() % 100000;
    }
    return vec;
}

std::vector<double> getRandomDoubleVector(int size, uint64_t seed) {
    std::vector<double> vec(size);
    std::mt19937 gen;
    gen.seed(seed);
    std::uniform_real_distribution<double> dist(-4200000.0, 4200000.0);
    for (int i = 0; i < size; ++i) {
        vec[i] = dist(gen);
    }
    return vec;
}
