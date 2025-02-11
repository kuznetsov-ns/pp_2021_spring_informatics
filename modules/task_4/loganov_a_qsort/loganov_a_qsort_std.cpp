// Copyright 2021 Loganov Andrei
#include <ctime>
#include <vector>
#include <random>
#include <algorithm>
#include "../../../../modules/task_4/loganov_a_qsort/loganov_a_qsort_std.h"
#include "../../../../3rdparty/unapproved/unapproved.h"
std::vector<double> getRandomVector(int size) {
    std::mt19937 gen;
    std::vector<double> result(size);
    const int start = 0;
    const int end = 1000;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::uniform_real_distribution<double> rand(start, end);
    for (int i = 0; i < static_cast<int>(result.size()); i++) {
    result[i] = rand(gen);
    }
    return result;
}
std::vector<double> copyvec(std::vector<double> vec) {
    std::vector<double> result(vec.size());
    for (int i = 0; i < static_cast<int>(vec.size()); i++) {
    result[i] = vec[i];
    }
    return result;
}
void Hoarsort(std::vector<double>* vec, int first, int last) {
    if (first >= last)return;
    int i = first, j = last;
    double  mid = (*vec)[(last + first) / 2];
    while (i <= j) {
    while ((*vec)[i] < mid) i++;
    while ((*vec)[j] > mid)j--;
    if (i < j) std::swap((*vec)[i], (*vec)[j]);
    if (i <= j) {
        i++;
        j--;
    }
    }
    Hoarsort(vec, first, j);
    Hoarsort(vec, i, last);
}
void MergePartsOfVector(double* vec1, int n1, int second, int n2) {
    int k = 0;
    int g = second;
    int f = 0;
    double* r = new double[(n1 + n2)];
     for (f = 0; k < n1 && g < static_cast<int64_t>(second + n2); f++) {
     if (vec1[k] < vec1[g]) {
         r[f] = vec1[k];
         k++;
     } else {
         r[f] = vec1[g];
         g++;
     }
     }
    if (g == second + n2) {
    for (int i = k; i < n1; i++) {
        r[f] = vec1[i];
        f++;
    }
    }
    if (k == n1) {
    for (int i = g; i < second + n2; i++) {
        r[f] = vec1[i];
        f++;
    }
    }
    int i = 0;
    while (i < n1 + n2) {
    vec1[i] = r[i];
    i++;
    }
    delete[] r;
}
void QsortSTD(std::vector<double>* vec) {
    int sz = (*vec).size();
    int threads_count = std::thread::hardware_concurrency();
    int delta = sz / threads_count;
    int remainder = sz % threads_count;
    std::vector<std::thread> threads;
    auto sort_f = [&](int id) {
        if (id == 0) {
            Hoarsort(vec, 0, delta + remainder - 1);
        } else {
            Hoarsort(vec, remainder + delta + delta * (id - 1),
            remainder + delta + delta * id - 1);
        }
    };
    for (int i = 0; i < threads_count; i++) {
        threads.emplace_back(std::thread(sort_f, i));
    }
    for (int i = 0; i < threads_count; i++) {
        threads[i].join();
    }
    int size = delta + remainder;
    for (int i = 1; i < threads_count; i++) {
        MergePartsOfVector(vec->data(), size,
            remainder + delta + delta * (i - 1), delta);
        size += delta;
    }
}

