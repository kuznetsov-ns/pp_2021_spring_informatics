// Copyright 2021 Novozhilova Ekaterina
#ifndef MODULES_TASK_2_NOVOZHILOVA_E_LABELING_LABELING_H_
#define MODULES_TASK_2_NOVOZHILOVA_E_LABELING_LABELING_H_

#include <vector>
#include <algorithm>
#include <cmath>

int check_for_par(std::vector<std::vector<int>> lab, int rows, int cols);
int check_for_seq(std::vector<std::vector<int>> lab, int rows, int cols);
std::vector<std::vector<int>> myrand(int n, int m, int nz);
std::vector<std::vector<int>> SeqLabeling(std::vector<std::vector<int>> arr,
int rows, int cols);
std::vector<std::vector<int>> ParLabeling(std::vector<std::vector<int>> arr,
int rows, int cols);

#endif  // MODULES_TASK_2_NOVOZHILOVA_E_LABELING_LABELING_H_
