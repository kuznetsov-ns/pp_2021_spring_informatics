// Copyright 2021 Bessolitsyn Sergay
#ifndef MODULES_TASK_3_BESSOLITSYN_S_QUICK_SORT_QUICK_SORT_H_
#define MODULES_TASK_3_BESSOLITSYN_S_QUICK_SORT_QUICK_SORT_H_

#include <tbb/tbb.h>
#include <tbb/blocked_range.h>
#include <tbb/parallel_for.h>

#include <vector>
#include <random>
#include <utility>

template<typename T>
void quick_sort(T arr[], int right) {
    if (right > 1) {
        int rand_id = std::rand() % right;
        int k = 0;
        std::swap(arr[0], arr[rand_id]);
        for (int i = 1; i < right; ++i) {
            if (arr[i] < arr[0]) {
                std::swap(arr[i], arr[++k]);
            }
        }
        std::swap(arr[0], arr[k]);
        quick_sort(arr, k);
        quick_sort(arr + k + 1, right - k - 1);
    }
}

template<typename T>
void merge(T arr1[], int size1, T arr2[], int size2) {
    T* tmp_arr = new T[size1 + size2];
    int i = 0, j = 0, k = 0;
    for (; i < size1 && j < size2; ++k) {
        if (arr1[i] < arr2[j])
            tmp_arr[k] = arr1[i++];
        else
            tmp_arr[k] = arr2[j++];
    }
    while (i < size1) {
        tmp_arr[k++] = arr1[i++];
    }
    while (j < size2) {
        tmp_arr[k++] = arr2[j++];
    }
    for (i = 0; i < k; ++i) {
        arr1[i] = tmp_arr[i];
    }
    delete[] tmp_arr;
}

template<typename T>
void quick_sort_TBB(std::vector<T>* vec) {
    int size = vec->size();
    int parts = 6;  // how many parts
    int delta = size / parts;  // a.k.a grainsize
    const int min_grainsize = 12;
    delta = (delta < min_grainsize) ? min_grainsize : delta;
    auto range = tbb::blocked_range<int>(0, size, delta);
    tbb::parallel_for(range, [&vec](const tbb::blocked_range<int>& range) {
        quick_sort(vec->data() + range.begin(), range.end() - range.begin());
    });
    int start = 0;
    for (int i = 1; i < size; i++) {
        if (vec->operator[](i - 1) > vec->operator[](i)) {
            if (start != 0) {
                merge(vec->data(), start, vec->data() + start, i - start);
            }
            start = i;
        }
    }
    merge(vec->data(), start, vec->data() + start, size - start);
}

std::vector<int> getRandomVector(int size, uint64_t seed = 50);
std::vector<double> getRandomDoubleVector(int size, uint64_t seed = 50);

#endif  // MODULES_TASK_3_BESSOLITSYN_S_QUICK_SORT_QUICK_SORT_H_
