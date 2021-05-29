// Copyright 2021 Pestreev Daniil

#include <functional>
#include <atomic>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <limits>
#include <utility>
#include <ctime>

#include "../../../../modules/task_4/pestreev_d_quick_sort_even_odd/quick_sort_even_odd_merge.h"
#include "../../../../3rdparty/unapproved/unapproved.h"

std::vector<std::pair<int, int>> comps;
std::vector<std::vector<int>> loc;

std::vector<int> getRandomVector(int size) {
    std::mt19937 gen;
    gen.seed(static_cast<unsigned int>(time(0)));
    std::vector<int> a(size);
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

std::vector<int> quickSortV(const std::vector<int>& vec) {
    int size = vec.size();
    if (size <= 1) {
        return vec;
    }
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = vec[i];
    }
    qsort(arr, 0, size - 1);
    std::vector<int> tmp;
    for (int i = 0; i < size; i++) {
        tmp.push_back(arr[i]);
    }
    delete[] arr;
    return tmp;
}

std::vector<std::vector<int>> div_into_part(const std::vector<int>& vec,
    int n) {
    std::vector<std::vector<int>> res;
    int vec_size = vec.size();
    int part_len = vec_size / n;
    int delta = 0;
    for (int i = 0; i < n; i++) {
        std::vector<int> a;
        for (int j = delta; j < delta + part_len; j++) {
            a.push_back(vec[j]);
        }
        res.push_back(a);
        delta += part_len;
    }
    return res;
}

void recur_merge(const std::vector<int>& left, const std::vector<int>& right) {
    int array_count = left.size() + right.size();
    if (array_count <= 1) {
        return;
    }
    if (array_count == 2) {
        comps.push_back(std::pair<int, int>(left[0], right[0]));
        return;
    }
    std::vector<int> left_odd;
    std::vector<int> left_even;
    std::vector<int> right_odd;
    std::vector<int> right_even;
    int leftsize = left.size();
    for (int i = 0; i < leftsize; i++) {
        if (i % 2) {
            left_even.push_back(left[i]);
        } else {
            left_odd.push_back(left[i]);
        }
    }
    int rightsize = right.size();
    for (int i = 0; i < rightsize; i++) {
        if (i % 2) {
            right_even.push_back(right[i]);
        } else {
            right_odd.push_back(right[i]);
        }
    }

    recur_merge(left_odd, right_odd);
    recur_merge(left_even, right_even);

    std::vector<int> res;
    for (int i = 0; i < leftsize; i++) {
        res.push_back(left[i]);
    }
    for (int i = 0; i < rightsize; i++) {
        res.push_back(right[i]);
    }

    for (int i = 1; i + 1 < array_count; i += 2) {
        comps.push_back(std::pair<int, int>(res[i], res[i + 1]));
    }
}

void networking(const std::vector<int>& arr) {
    int arr_size = arr.size();

    if (arr_size <= 1) {
        return;
    }

    std::vector<int> l(arr.begin(), arr.begin() + arr_size / 2);
    std::vector<int> r(arr.begin() + arr_size / 2, arr.begin() + arr_size);
    networking(l);
    networking(r);
    recur_merge(l, r);
}

void batchers_network(int thread_size) {
    if (thread_size <= 1)
        return;
    std::vector<int> procs;
    for (int i = 0; i < thread_size; i++) {
        procs.push_back(i);
    }

    networking(procs);
}

class Mybarrier {
    const unsigned int threadCount;
    std::atomic<unsigned int> threadsWait;
    std::mutex m;
    std::condition_variable cond_var;
 public:
    explicit Mybarrier(unsigned int n) : threadCount(n), threadsWait(0) {
        //  threadsWait = 0;
    }
    Mybarrier(const Mybarrier &) = delete;
    void wait() {
        std::unique_lock<std::mutex> lock(m);
        if (threadsWait.fetch_add(1) >= threadCount - 1) {
            threadsWait.store(0);
            cond_var.notify_all();
        } else {
            cond_var.wait(lock);
        }
    }
};

Mybarrier *myBarrier;

void exchangeBetweenProcesses(int id, int comps_size, int vecsizeL) {
    for (int i = 0; i < comps_size; i++) {
        std::vector<int> localV(vecsizeL);
        std::vector<int> neighboringV(vecsizeL);
        std::vector<int> tmpV(vecsizeL);
        if (id == comps[i].first) {
            localV = loc[id];
            neighboringV = loc[comps[i].second];
            int localidx = 0;
            int neighboridx = 0;
            for (int tmp_index = 0; tmp_index < vecsizeL; tmp_index++) {
                int local = localV[localidx];
                int neighbor = neighboringV[neighboridx];
                if (local < neighbor) {
                    tmpV[tmp_index] = local;
                    localidx++;
                } else {
                    tmpV[tmp_index] = neighbor;
                    neighboridx++;
                }
            }
            myBarrier->wait();
            loc[id] = tmpV;
        } else if (id == comps[i].second) {
            localV = loc[id];
            neighboringV = loc[comps[i].first];
            int start = vecsizeL - 1;
            int localidx = start;
            int neighboridx = start;
            for (int tmp_index = start; tmp_index >= 0; tmp_index--) {
                int local = localV[localidx];
                int neighbor = neighboringV[neighboridx];
                if (local > neighbor) {
                    tmpV[tmp_index] = local;
                    localidx--;
                } else {
                    tmpV[tmp_index] = neighbor;
                    neighboridx--;
                }
            }
            myBarrier->wait();
            loc[id] = tmpV;

        } else if ((id != comps[i].second)) {
            if ((id != comps[i].first)) {
                myBarrier->wait();
            }
        }
        myBarrier->wait();
    }
}


std::vector<int> parallel_sorting(const std::vector<int>& vec,
    int thread_size) {
    std::vector<int> globalV = vec;
    int vecsizeG = globalV.size();

    if (thread_size < 0) {
        return globalV;
    }

    if (thread_size >= vecsizeG || thread_size == 1) {
        globalV = quickSortV(vec);
        return globalV;
    }
    int exitcircle = -1;
    int vecsizechange = 0;
    while (exitcircle < 0) {
        exitcircle = -1;
        if (globalV.size() % thread_size) {
            int o = std::numeric_limits<int>::max();
            vecsizechange++;
            globalV.push_back(o);
        } else {
            exitcircle = 1;
        }
    }
    vecsizeG = globalV.size();

    int vecsizeL = vecsizeG / thread_size;
    loc = div_into_part(globalV, thread_size);
    batchers_network(thread_size);
    int comps_size = comps.size();
    std::vector<std::thread> threads(thread_size);
    int nloop = thread_size;
    for (int t = 0; t < thread_size; t++) {
        int begin_i = t * nloop / thread_size;
        int end_i = 0;
        if ((t+1) == thread_size) {
            end_i = nloop;
        } else {
            end_i = (t + 1) * nloop / thread_size;
        }
        threads[t] = std::thread(std::bind(
            [&](const int bi, const int ei, const int t) {
                for (int i = bi; i < ei; i++) {
                    const std::vector<int> v = loc[i];
                    loc[i] = quickSortV(v);
                }
            }, begin_i, end_i, t));
    }

    std::for_each(threads.begin(), threads.end(),
        [](std::thread& x) {x.join();});

    myBarrier = new Mybarrier(thread_size);

    std::thread* ts = new std::thread[thread_size];
    for (int i = 0; i < thread_size; i++) {
        ts[i] = std::thread(exchangeBetweenProcesses, i, comps_size, vecsizeL);
    }

    for (int i = 0; i < thread_size; i++) {
        ts[i].join();
    }

    delete myBarrier;

    std::vector<int> res;
    int size = thread_size;
    int size_m_s = vecsizeG / thread_size;

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size_m_s; j++) {
            res.push_back(loc[i][j]);
        }
    if (vecsizechange > 0)
        res.erase(res.begin() + vecsizeG - vecsizechange,
            res.begin() + vecsizeG);
    delete[] ts;
    return res;
}
