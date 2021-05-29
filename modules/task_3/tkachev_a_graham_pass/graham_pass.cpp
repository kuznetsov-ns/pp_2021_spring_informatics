// Copyright 2021 Tkachev Alexey

#include "../../../modules/task_3/tkachev_a_graham_pass/graham_pass.h"

std::vector<Point> getRandomizedVector(double from,
                        double up_to, uint32_t count) {
    assert(from < up_to);
    assert(count > 0);
    std::mt19937 random_generator(time(NULL));
    std::uniform_real_distribution<double> real_dist(from, up_to);
    std::vector<Point> randomized_vector(count);

    for (std::size_t i = 0; i < count; i++) {
        randomized_vector[i].x = real_dist(random_generator);
        randomized_vector[i].y = real_dist(random_generator);
    }

    return randomized_vector;
}

void swapPoints(Point* p1, Point* p2) {
    std::swap(p1->x, p2->x);
    std::swap(p1->y, p2->y);
}

Point nextToTopOfStack(std::stack<Point> points) {
    assert(!points.empty());
    const Point tmp = points.top();
    points.pop();
    const Point result = points.top();
    points.push(tmp);
    return result;
}

double angleThreePoints(Point p1, Point p2, Point p3) {
     return (p2.x - p1.x) * (p3.y - p1.y) -
            (p2.y - p1.y) * (p3.x - p1.x);
}

double distanceTwoPoints(Point p1, Point p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) +
                (p2.y - p1.y) * (p2.y - p1.y));
}

std::vector<Point> sortedByPolarAngleTBB(
            std::vector<Point> points, bool multithreading) {
    assert(!points.empty());

    if (multithreading) {
            tbb::task_scheduler_init init;
            tbb::spin_mutex mutex_;

            std::size_t grainsize_ = points.size() / 8;

            for (std::size_t i = 2; i < points.size(); i++)
                tbb::parallel_for(tbb::blocked_range<std::size_t>(
                    2, points.size(), grainsize_),
                [&](const tbb::blocked_range<std::size_t>& r) {
                    for (std::size_t j = r.begin(); j < r.end(); j++) {
                        double current_angle = angleThreePoints(
                                    points[j-1], points[j], points[0]);
                        if (current_angle < 0) {
                            tbb::spin_mutex::scoped_lock lock;
                            lock.acquire(mutex_);
                            swapPoints(&points[j-1], &points[j]);
                            lock.release();
                        } else {
                            if (current_angle == 0) {
                                if (distanceTwoPoints(points[j], points[0]) <
                                    distanceTwoPoints(points[j-1], points[0])) {
                                    tbb::spin_mutex::scoped_lock lock;
                                    lock.acquire(mutex_);
                                    swapPoints(&points[j-1], &points[j]);
                                    lock.release();
                                }
                            }
                        }
                    }
                });
            init.terminate();
    } else {
        for (std::size_t i = 2; i < points.size(); i++) {
            for (std::size_t j = 2; j < points.size(); j++) {
                double current_angle = angleThreePoints(
                                    points[j-1], points[j], points[0]);
                if (current_angle < 0) {
                    swapPoints(&points[j-1], &points[j]);
                } else {
                    if (current_angle == 0) {
                        if (distanceTwoPoints(points[j], points[0]) <
                            distanceTwoPoints(points[j-1], points[0])) {
                            swapPoints(&points[j-1], &points[j]);
                        }
                    }
                }
            }
        }
    }
    return points;
}

uint32_t getIndexMinLeftDownPoint(
                std::vector<Point> points, bool multithreading) {
    assert(!points.empty());

    double min_x = std::numeric_limits<double>::max();
    double min_y = std::numeric_limits<double>::max();

    std::vector<double> min_xs
    (100, std::numeric_limits<double>::max()),
    min_ys
    (100, std::numeric_limits<double>::max());

    if (multithreading) {
        tbb::task_scheduler_init init;

        std::size_t grainsize_ = points.size() / 8;

        tbb::parallel_for(tbb::blocked_range<std::size_t>(
            0, points.size(), grainsize_),
        [&](const tbb::blocked_range<std::size_t>& r) {
            std::size_t ind = tbb::task_arena::current_thread_index();
            for (std::size_t i = r.begin(); i < r.end(); i++) {
                if (min_ys[ind] > points[i].y) {
                    min_ys[ind] = points[i].y;
                }
            }
        });

        min_y = *std::min_element(min_ys.begin(), min_ys.end());

        tbb::parallel_for(tbb::blocked_range<std::size_t>(
            0, points.size(), grainsize_),
        [&](const tbb::blocked_range<std::size_t>& r) {
            std::size_t ind = tbb::task_arena::current_thread_index();
            for (std::size_t i = r.begin(); i < r.end(); i++) {
                if (points[i].y == min_y &&
                    min_xs[ind] > points[i].x) {
                    min_xs[ind] = points[i].x;
                }
            }
        });
        min_x = *std::min_element(min_xs.begin(), min_xs.end());
        init.terminate();
    } else {
        for (std::size_t i = 0; i < points.size(); i++) {
            if (points[i].y < min_y) {
                min_y = points[i].y;
            }
        }
        for (std::size_t i = 0; i < points.size(); i++) {
            if (points[i].y == min_y) {
                if (points[i].x < min_x) {
                    min_x = points[i].x;
                }
            }
        }
    }
    for (std::size_t i = 0; i < points.size(); i++) {
        if (points[i].x == min_x && points[i].y == min_y) {
            return i;
        }
    }
    throw;
}

std::stack<Point> useGrahamAlgorithm(
            std::vector<Point> points, bool multithreading) {
    assert(!points.empty());

    std::stack<Point> points_stack;

    if (points.size() <= 3) {
        for (std::size_t i = 0; i < points.size(); i++) {
            points_stack.push(points[i]);
        }
        points_stack.push(points[0]);
        return points_stack;
    }

    swapPoints(&points[0],
        &points[getIndexMinLeftDownPoint(points, multithreading)]);

    points = sortedByPolarAngleTBB(points, multithreading);

    points.push_back(points[0]);

    points_stack.push(points[0]);
    points_stack.push(points[1]);
    points_stack.push(points[2]);

    for (std::size_t i = 3; i < points.size(); i++) {
        while (
            angleThreePoints(
                nextToTopOfStack(points_stack),
                points_stack.top(),
                points[i]) <= 0) {
            if (!points_stack.empty()) {
                points_stack.pop();
            }
        }
        points_stack.push(points[i]);
    }
    return points_stack;
}
