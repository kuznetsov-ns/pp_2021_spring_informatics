// Copyright 2021 Yurin Stanislav
#ifndef MODULES_TASK_3_YURIN_S_STRASSEN_ALGORITHM_STRASSEN_ALGORITHM_H_
#define MODULES_TASK_3_YURIN_S_STRASSEN_ALGORITHM_STRASSEN_ALGORITHM_H_

#include <vector>
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/tick_count.h"

enum HorAnglePos {
    left, right
};

enum VertAnglePos {
    up, down
};

unsigned int get_random_time();
double getRandomNumber(int min, int max);

std::vector<double>::const_iterator getSubMatrConstIter(HorAnglePos, VertAnglePos);
std::vector<double> StrassenMultiOMP(const std::vector<double>&, const std::vector<double>&);
std::vector<double> StrassenMultiTBB(const std::vector<double>&, const std::vector<double>&);

void matrSum(std::vector<double>::const_iterator a_it,
    std::vector<double>::const_iterator b_it,
    std::vector<double>::iterator m_it,
    int m_rows_num);

void matrDiff(std::vector<double>::const_iterator a_it,
    std::vector<double>::const_iterator b_it,
    std::vector<double>::iterator m_it,
    int m_rows_num);

void matrSum(const std::vector<double>& m1,
    const std::vector<double>& m2,
    std::vector<double>::iterator c_it);

void matrDiff(const std::vector<double>& m1,
    const std::vector<double>& m2,
    std::vector<double>::iterator c_it);

void matrSum(std::vector<double>::iterator c_it,
    const std::vector<double>& m1);

void matrDiff(std::vector<double>::iterator c_it,
    const std::vector<double>& m1);

void matrMultiSEQ(const std::vector<double>& p1,
    const std::vector<double>& p2,
    std::vector<double>::iterator m_it,
    int m_rows_num);

void matrMultiOMP(std::vector<double>::const_iterator a_it,
    const std::vector<double>& p2,
    std::vector<double>::iterator m_it,
    int m_rows_num);

void matrMultiOMP(const std::vector<double>& p2,
    std::vector<double>::const_iterator a_it,
    std::vector<double>::iterator m_it,
    int m_rows_num);

void matrMultiOMP(const std::vector<double>& p1,
    const std::vector<double>& p2,
    std::vector<double>::iterator m_it,
    int m_rows_num);

void matrMultiTBB(std::vector<double>::const_iterator a_it,
    const std::vector<double>& p2,
    std::vector<double>::iterator m_it,
    int m_rows_num);

void matrMultiTBB(const std::vector<double>& p2,
    std::vector<double>::const_iterator a_it,
    std::vector<double>::iterator m_it,
    int m_rows_num);

void matrMultiTBB(const std::vector<double>& p1,
    const std::vector<double>& p2,
    std::vector<double>::iterator m_it,
    int m_rows_num);

#endif  // MODULES_TASK_3_YURIN_S_STRASSEN_ALGORITHM_STRASSEN_ALGORITHM_H_
