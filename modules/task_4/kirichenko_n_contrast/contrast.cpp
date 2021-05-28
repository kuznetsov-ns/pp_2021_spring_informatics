// Copyright 2021 Kirichenko Nikita
#include "../../../modules/task_4/kirichenko_n_contrast/contrast.h"
#include "../../../3rdparty/unapproved/unapproved.h"

Result RandomI(int l, int k) {
    if (l <= 0 || k <= 0)
        throw std::runtime_error("Incorrect data !");
    static std::mt19937 random(time(0));
    Result res(l * k);
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < k; j++) {
            res[i * l + j] = random() % 256;
        }
    }
    return res;
}

Result Contrast(const Result& rm) {
    Result outcome(rm.size());
    int max = 0;
    int min = 255;
    for (int i = 0; i < static_cast<int>(rm.size()); i++) {
        if (min > rm[i])
            min = rm[i];
        if (max < rm[i])
            max = rm[i];
    }
    for (int i = 0; i < static_cast<int>(rm.size()); i++) {
        outcome[i] = (rm[i] - min) * (255 / (max - min));
    }
    return outcome;
}

Result Contraststd(const Result& rm) {
    Result outcome(rm.size());
    int min = 255, max = 0;

    int const numThreads = 4;

    int delta = static_cast<int>(rm.size()) / numThreads;
    std::vector<int> limits(numThreads + 1);
    for (int i = 0; i < numThreads; i++) {
        limits[i] = i * delta;
    }

    limits[numThreads] = static_cast<int>(rm.size());

    std::vector <std::pair<int, int>> min_max_arr(numThreads);

    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; i++) {
        std::thread thr([&rm, &limits, &min_max_arr](int id_thread) -> void {
            std::pair<int, int> result(255, 0);
            for (int i = limits[id_thread]; i < limits[id_thread + 1]; i++) {
                if (rm[i] > result.second) {
                    result.second = rm[i];
                }
                if (rm[i] < result.first) {
                    result.first = rm[i];
                }
            }
            min_max_arr[id_thread] = result;
            }, i);
        threads.emplace_back(std::move(thr));
    }
    for (int i = 0; i < numThreads; i++) {
        threads[i].join();
    }

    for (auto& temp : min_max_arr) {
        if (temp.second > max) {
            max = temp.second;
        }
        if (temp.first < min) {
            min = temp.first;
        }
    }

    std::vector<std::thread> threads1;
    for (int i = 0; i < numThreads; i++) {
        std::thread thr([&](const int i) {
            for (int j = limits[i]; j < limits[i + 1]; j++)
                outcome[j] = ((rm[j] - min) * 255) / (max - min);
            }, i);
        threads1.emplace_back(std::move(thr));
    }
    for (int i = 0; i < numThreads; i++) {
        threads1[i].join();
    }
    return outcome;
}
