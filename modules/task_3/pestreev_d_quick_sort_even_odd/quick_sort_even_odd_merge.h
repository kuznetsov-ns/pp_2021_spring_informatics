// Copyright 2021 Pestreev Daniil
#ifndef MODULES_TASK_3_PESTREEV_D_QUICK_SORT_EVEN_ODD_QUICK_SORT_EVEN_ODD_MERGE_H_
#define MODULES_TASK_3_PESTREEV_D_QUICK_SORT_EVEN_ODD_QUICK_SORT_EVEN_ODD_MERGE_H_

#include <vector>
int* getRandomArray(int size);
std::vector<int> getRandomVector(int size);
void Swap(int a, int b);
void qsort(int* vec, int left, int right);
std::vector<int> quickSortV(const std::vector<int>& vec);
class EvenSplitter;
class OddSplitter;
class parallel_sorting;
void parallel_sorting_int(int* inp, int size, int nThreads);

bool CompareArrays(int* mas, int* Mas, int size);

#endif  // MODULES_TASK_3_PESTREEV_D_QUICK_SORT_EVEN_ODD_QUICK_SORT_EVEN_ODD_MERGE_H_
