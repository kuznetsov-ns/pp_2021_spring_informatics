// Copyright 2021 Kirichenko Nikita
#ifndef MODULES_TASK_4_KIRICHENKO_N_CONTRAST_CONTRAST_H_
#define MODULES_TASK_4_KIRICHENKO_N_CONTRAST_CONTRAST_H_

#include <iostream>
#include <cstdint>
#include <random>
#include <vector>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <limits>
#include <utility>

using Result = std::vector<int>;

Result RandomI(int l, int k);
Result Contrast(const Result& rm);
Result Contraststd(const Result& rm);

#endif  // MODULES_TASK_4_KIRICHENKO_N_CONTRAST_CONTRAST_H_
