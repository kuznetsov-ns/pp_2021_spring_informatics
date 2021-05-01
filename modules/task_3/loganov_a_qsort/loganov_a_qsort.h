// Copyright 2021 Loganov Andrei
#ifndef MODULES_TASK_3_LOGANOV_A_QSORT_LOGANOV_A_QSORT_H_
#define MODULES_TASK_3_LOGANOV_A_QSORT_LOGANOV_A_QSORT_H_
#include <vector>
std::vector<double> getRandomVector(int size);
void Hoarsort(std::vector<double>* vec, int first, int last);
void MergePartsOfVector(double* vec1, int n1, int second, int n2);
void QsortTBB(std::vector<double>* vec, int threads_count = 4);
std::vector<double> copyvec(std::vector<double> vec);
#endif  // MODULES_TASK_3_LOGANOV_A_QSORT_LOGANOV_A_QSORT_H_
