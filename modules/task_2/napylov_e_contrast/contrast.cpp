// Copyright 2021 Napylov Evgenii

#include <iostream>
#include <cassert>
#include <random>
#include <ctime>
#include <algorithm>

#include "../../../modules/task_2/napylov_e_contrast/contrast.h"

void print_vec(const VecImage& vec) {
    for (auto val : vec) {
        std::cout << static_cast<int>(val) << ' ';
    }
    std::cout << std::endl;
}

VecImage RandomVector(int size) {
    static std::mt19937 gen(time(0));
    VecImage result(size);
    std::uniform_int_distribution<unsigned int> distr(0, 255);
    for (int i = 0; i < size; i++) {
        result[i] = static_cast<unsigned char>(distr(gen));
    }
    return result;
}

VecImage add_contrast(VecImage image) {
    unsigned char min = *std::min_element(image.begin(), image.end());
    unsigned char max = *std::max_element(image.begin(), image.end());
    if (max == min) {
        return image;
    } else {
        for (size_t i = 0; i < image.size(); i++) {
            image[i] = round((static_cast<double>((image[i] - min))
                / static_cast<double>((max - min)))* 255);
        }
        return image;
    }
}

std::pair<unsigned char, unsigned char> minmax_omp(const VecImage& image) {
    unsigned char min_col = 255;
    unsigned char max_col = 0;

    int max_threads = omp_get_max_threads();
    std::vector<unsigned char> min_vec(max_threads);
    std::fill(min_vec.begin(), min_vec.end(), 255);
    std::vector<unsigned char> max_vec(max_threads);
    std::fill(max_vec.begin(), max_vec.end(), 0);

    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < static_cast<int>(image.size()); i++) {
            if (image[i] > max_vec[thread_id]) {
                max_vec[thread_id] = image[i];
            }
            if (image[i] < min_vec[thread_id]) {
                min_vec[thread_id] = image[i];
            }
        }
    }
    // Reduction
    max_col = *std::max_element(max_vec.begin(), max_vec.end());
    min_col = *std::min_element(min_vec.begin(), min_vec.end());
    return std::pair<unsigned char, unsigned char>(min_col, max_col);
}

VecImage add_contrast_omp(VecImage image) {
    std::pair<unsigned char, unsigned char> minmax = minmax_omp(image);
    unsigned char min_col = minmax.first;
    unsigned char max_col = minmax.second;

    if (max_col == min_col) {
        return image;
    } else {
        #pragma omp parallel for
        for (int i = 0; i < static_cast<int>(image.size()); i++) {
            image[i] = round((static_cast<double>((image[i] - min_col))
                / static_cast<double>((max_col - min_col))) * 255);
        }
        return image;
    }
}
