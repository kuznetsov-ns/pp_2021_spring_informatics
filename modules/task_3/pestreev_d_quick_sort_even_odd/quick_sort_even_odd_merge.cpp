// Copyright 2021 Pestreev Daniil

#include "../../../modules/task_3/pestreev_d_quick_sort_even_odd/quick_sort_even_odd_merge.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <utility>
#include <ctime>
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

int* getRandomArray(int size) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    int* a = new int[size];
    for (int i = 0; i < size; i++) {
        a[i] = gen();
    }
    return a;
}

void qsort(int* vec, int left, int right) {
    int mid;
    int l = left;
    int r = right;
    mid = vec[(l + r) / 2];
    do {
        while (vec[l] < mid) l++;
        while (vec[r] > mid) r--;
        if (l <= r) {
            std::swap(vec[l], vec[r]);
            l++;
            r--;
        }
    } while (l < r);
    if (left < r) qsort(vec, left, r);
    if (l < right) qsort(vec, l, right);
}

class evenSplit:public tbb::task {
 private:
    int *mass;
    int *mas_even;
    int size_mass;
    int size_mas_even;

 public:
    evenSplit(int *_mass, int *_mas_even, int _size_mass,
                int _size_mas_even): mass(_mass), mas_even(_mas_even),
                size_mass(_size_mass), size_mas_even(_size_mas_even)
    {}

    tbb::task* execute() {
        for (int i = 0; i < size_mass; i += 2)
            mas_even[i] = mass[i];
        int* other = new int[size_mass];
        for (int j = 0; j < size_mass; j++) {
            other[j] = mass[j + size_mass];
        }

        int a = 0;
        int b = 0;
        int i = 0;
        while ((a < size_mass) && (b < size_mas_even)) {
            if (mas_even[a] <= other[b]) {
                mass[i] = mas_even[a];
                a+=2;
            } else {
                mass[i] = other[b];
                b+=2;
            }
            i += 2;
        }

        if (a == size_mass) {
            for (int j = b; j < size_mas_even; j+=2, i+=2)
                mass[i] = other[j];
        } else {
            for (int j = a; j < size_mass; j+=2, i+=2)
                mass[i] = mas_even[j];
        }

        return NULL;
    }
};

class oddSplit:public tbb::task {
 private:
    int *mass;
    int *mas_odd;
    int size_mass;
    int size_mas_odd;

 public:
    oddSplit(int *_mass, int *_mas_odd, int _size_mass,
                int _size_mas_odd): mass(_mass), mas_odd(_mas_odd),
                size_mass(_size_mass), size_mas_odd(_size_mas_odd)
    {}

    tbb::task* execute() {
    for (int i = 1; i < size_mass; i+=2)
        mas_odd[i] = mass[i];

    int* other = new int[size_mass];
    for (int j = 0; j < size_mass; j++) {
        other[j] = mass[j + size_mass];
    }

    int a = 1;
    int b = 1;
    int i = 1;
    while ((a < size_mass) && (b < size_mas_odd)) {
        if (mas_odd[a] <= other[b]) {
            mass[i] = mas_odd[a];
            a+=2;
        } else {
            mass[i] = other[b];
            b+=2;
        }
        i += 2;
    }

    if (a == size_mass) {
    for (int j = b; j < size_mas_odd; j+=2, i+=2)
        mass[i] = other[j];
    } else {
    for (int j = a; j < size_mass; j+=2, i+=2)
        mass[i] = mas_odd[j];
    }

    return NULL;
    }
};

class parallel_sorting:public tbb::task {
 private:
    int *mas;
    int *tmp;
    int size;
    int part;

 public:
    parallel_sorting(int *_mas, int *_tmp, int _size,
        int _part): mas(_mas), tmp(_tmp),
        size(_size), part(_part)
    {}

    tbb::task* execute() {
        if (size <= part) {
        qsort(mas, 0, size - 1);
        } else {
        int s = size / 2 + (size/2)%2;

        parallel_sorting &sorter1 = *new (allocate_child())
                parallel_sorting(&mas[0], tmp, s, part);
        parallel_sorting &sorter2 = *new (allocate_child())
                parallel_sorting(&mas[s], tmp + s, size - s,
                                part);

        set_ref_count(3);

        spawn(sorter1);
        spawn_and_wait_for_all(sorter2);

        evenSplit &splitter1 = *new (allocate_child())
                evenSplit(&mas[0], tmp, s, size - s);
        oddSplit &splitter2 = *new (allocate_child())
                oddSplit(&mas[0], tmp, s, size - s);

        set_ref_count(3);

        spawn(splitter1);
        spawn_and_wait_for_all(splitter2);

        parallel_for(tbb::blocked_range<size_t>(1, (size+1)/2),
            [&](const tbb::blocked_range<size_t>& r) {
                for (size_t i = r.begin(); i < r.end(); i++)
                if (mas[2*i] < mas[2*i-1]) {
                    int _tmp = mas[2*i-1];
                    mas[2*i-1] = mas[2*i];
                    mas[2*i] = _tmp;
                }
            });
        }
        return NULL;
    }
};

void parallel_sorting_int(int* mass, int size, int thread_size) {
    if (size <= 1) {
        return;
    } else {
        int* mass_change;
        int* tmp = new int[size];
        int part = size / thread_size;
        bool change = false;
        if (size % thread_size != 0) {
        change = true;
            mass_change = new int[size + size % thread_size];
            for (int i = 0; i < size; i++) {
                mass_change[i] = mass[i];
            }
            for (int i = size; i < size % thread_size; i++) {
            int o = std::numeric_limits<int>::max();
            mass_change[i] = o;
            }
        }
        if (change) {
        parallel_sorting& sorter = *new (tbb::task::allocate_root())
            parallel_sorting(mass_change, tmp, size, part);
        tbb::task::spawn_root_and_wait(sorter);
        for (int i = 0; i < size; i++) {
            mass[i] = mass_change[i];
            }
            delete[] mass_change;
        } else {
            parallel_sorting& sorter = *new (tbb::task::allocate_root())
            parallel_sorting(mass, tmp, size, part);
        tbb::task::spawn_root_and_wait(sorter);
        }

        delete[] tmp;
    }
}

bool CompareArrays(int* mas, int* Mas, int size) {
    for (int i = 0; i < size; i++)
        if (mas[i] != Mas[i])
            return false;
    return true;
}
