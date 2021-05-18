// Copyright 2021 Tkachev Alexey

#ifndef MODULES_TASK_3_TKACHEV_A_GRAHAM_PASS_GRAHAM_PASS_H_
#define MODULES_TASK_3_TKACHEV_A_GRAHAM_PASS_GRAHAM_PASS_H_

#include <vector>
#include <stack>
#include <cstdint>
#include <random>
#include <ctime>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <climits>
#include <utility>
#include "tbb/task_scheduler_init.h"
#include "tbb/parallel_for.h"
#include "tbb/spin_mutex.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_sort.h"

struct Point {double x, y;};

std::vector<Point> getRandomizedVector(
    double from, double up_to, uint32_t count);

double angleThreePoints(Point p1, Point p2, Point p3);
double distanceTwoPoints(Point p1, Point p2);

void swapPoints(Point* p1, Point* p2);
Point nextToTopOfStack(std::stack<Point> points);

std::vector<Point> sortedByPolarAngle(
    std::vector<Point> points, bool multithreading);

uint32_t getIndexMinLeftDownPoint(
    std::vector<Point> points, bool multithreading);

std::stack<Point> useGrahamAlgorithm(
    std::vector<Point> points, bool multithreading);

#endif  // MODULES_TASK_3_TKACHEV_A_GRAHAM_PASS_GRAHAM_PASS_H_
