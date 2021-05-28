// Copyright 2021 Pestreev Daniil
#include <gtest/gtest.h>
#include <vector>
#include "tbb/tbb.h"
#include "tbb/parallel_sort.h"
#include "./quick_sort_even_odd_merge.h"

TEST(pestreev_d_quick_sort_even_odd, Test_manual_array) {
    int size = 14;
    std::vector<int> vec = {-8098, 1009, -160, -1, 179796, 2,
        -1603, 166, -7396, -19, -18348, -15, 7, 82519};

    int* Array = new int[size];
    for (int i = 0; i < size; i++) {
        Array[i] = vec[i];
    }
    int* Array_copy = new int[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    parallel_sorting_int(Array, size, 2);
    for (int i = 0; i < size; i++) {
        std::cout << Array[i] << " ";
    }
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(pestreev_d_quick_sort_even_odd, Test_random_array_0_2) {
    int size = 0;
    int* Array = getRandomArray(size);
    int* Array_copy = new int[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    parallel_sorting_int(Array, size, 2);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(pestreev_d_quick_sort_even_odd, Test_random_array_0_4) {
    int size = 0;
    int* Array = getRandomArray(size);
    int* Array_copy = new int[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    parallel_sorting_int(Array, size, 4);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(pestreev_d_quick_sort_even_odd, Test_random_array_1_2) {
    int size = 1;
    int* Array = getRandomArray(size);
    int* Array_copy = new int[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    parallel_sorting_int(Array, size, 2);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(pestreev_d_quick_sort_even_odd, Test_random_array_1_4) {
    int size = 1;
    int* Array = getRandomArray(size);
    int* Array_copy = new int[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    parallel_sorting_int(Array, size, 4);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(pestreev_d_quick_sort_even_odd, Test_random_array_100_4) {
    int size = 100;
    int* Array = getRandomArray(size);
    int* Array_copy = new int[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }
    parallel_sorting_int(Array, size, 4);
    tbb::parallel_sort(Array_copy, Array_copy + size);
    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}

TEST(pestreev_d_quick_sort_even_odd, Test_sorted_vector1211_2) {
    int size = 1211;
    int* Array = getRandomArray(size);
    std::vector<int> vec;
    for (int i = 0; i < size; i++) {
        vec.push_back(Array[i]);
    }
    std::sort(vec.begin(), vec.end());
    parallel_sorting_int(Array, size, 2);
    std::vector<int> vec_s;
    for (int i = 0; i < size; i++) {
        vec_s.push_back(Array[i]);
    }
    ASSERT_EQ(vec, vec_s);
}

TEST(pestreev_d_quick_sort_even_odd, Test_inverted_sorted_vector1211_2) {
    int size = 1211;
    int* Array = getRandomArray(size);
    std::vector<int> vec;
    for (int i = 0; i < size; i++) {
        vec.push_back(Array[i]);
    }
    std::sort(vec.begin(), vec.end(), [](int a, int b){
        return a > b;
    });
    for (int i = 0; i < size; i++) {
        Array[i] = vec[i];
    }
    std::sort(vec.begin(), vec.end());
    parallel_sorting_int(Array, size, 2);
    std::vector<int> vec_s;
    for (int i = 0; i < size; i++) {
        vec_s.push_back(Array[i]);
    }
    ASSERT_EQ(vec, vec_s);
}

TEST(pestreev_d_quick_sort_even_odd, Test_on_40000_tbbsort) {
    int size = 40000;
    int* Array = getRandomArray(size);
    int* Array_copy = new int[size];
    for (int i = 0; i < size; i++) {
        Array_copy[i] = Array[i];
    }

    parallel_sorting_int(Array, size, 4);
    qsort(Array_copy, 0, size - 1);

    ASSERT_EQ(1, CompareArrays(Array, Array_copy, size));
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
