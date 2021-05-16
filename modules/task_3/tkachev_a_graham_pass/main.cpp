// Copyright 2021 Tkachev Alexey

#include <gtest/gtest.h>

#include "../../../modules/task_3/tkachev_a_graham_pass/graham_pass.h"

TEST(test_tkachev_a_graham_pass, test_m500_500_100) {
    const uint64_t SIZE = 100;
    const int FROM = -500;
    const int TO = 500;

    std::vector<Point> const points =
            getRandomizedVector(FROM, TO, SIZE);

    std::stack<Point> not_parallel =
            useGrahamAlgorithm(points, false);

    std::stack<Point> parallel =
            useGrahamAlgorithm(points, true);

    std::vector<double> x_no_parallel(not_parallel.size()),
                        y_no_parallel(not_parallel.size());

    for (std::size_t i = 0; !not_parallel.empty() &&
                        i < x_no_parallel.size(); i++) {
        x_no_parallel[i] = not_parallel.top().x;
        y_no_parallel[i] = not_parallel.top().y;
        not_parallel.pop();
    }

    std::vector<double> x_parallel(parallel.size()),
                        y_parallel(parallel.size());
    for (std::size_t i = 0; !parallel.empty() &&
                        i < x_parallel.size(); i++) {
        x_parallel[i] = parallel.top().x;
        y_parallel[i] = parallel.top().y;
        parallel.pop();
    }

    ASSERT_EQ(x_parallel, x_no_parallel);
    ASSERT_EQ(y_parallel, y_no_parallel);
}

TEST(test_tkachev_a_graham_pass, test_0_100_1000) {
    const uint64_t SIZE = 1000;
    const int FROM = 0;
    const int TO = 100;

    std::vector<Point> const points =
            getRandomizedVector(FROM, TO, SIZE);

    std::stack<Point> not_parallel =
            useGrahamAlgorithm(points, false);

    std::stack<Point> parallel =
            useGrahamAlgorithm(points, true);

    std::vector<double> x_no_parallel(not_parallel.size()),
                        y_no_parallel(not_parallel.size());

    for (std::size_t i = 0; !not_parallel.empty() &&
                        i < x_no_parallel.size(); i++) {
        x_no_parallel[i] = not_parallel.top().x;
        y_no_parallel[i] = not_parallel.top().y;
        not_parallel.pop();
    }

    std::vector<double> x_parallel(parallel.size()),
                        y_parallel(parallel.size());
    for (std::size_t i = 0; !parallel.empty() &&
                        i < x_parallel.size(); i++) {
        x_parallel[i] = parallel.top().x;
        y_parallel[i] = parallel.top().y;
        parallel.pop();
    }

    ASSERT_EQ(x_parallel, x_no_parallel);
    ASSERT_EQ(y_parallel, y_no_parallel);
}

TEST(test_tkachev_a_graham_pass, test_0_1_100) {
    const uint64_t SIZE = 100;
    const int FROM = 0;
    const int TO = 1;

    std::vector<Point> const points =
            getRandomizedVector(FROM, TO, SIZE);

    std::stack<Point> not_parallel =
            useGrahamAlgorithm(points, false);

    std::stack<Point> parallel =
            useGrahamAlgorithm(points, true);

    std::vector<double> x_no_parallel(not_parallel.size()),
                        y_no_parallel(not_parallel.size());

    for (std::size_t i = 0; !not_parallel.empty() &&
                        i < x_no_parallel.size(); i++) {
        x_no_parallel[i] = not_parallel.top().x;
        y_no_parallel[i] = not_parallel.top().y;
        not_parallel.pop();
    }

    std::vector<double> x_parallel(parallel.size()),
                        y_parallel(parallel.size());
    for (std::size_t i = 0; !parallel.empty() &&
                        i < x_parallel.size(); i++) {
        x_parallel[i] = parallel.top().x;
        y_parallel[i] = parallel.top().y;
        parallel.pop();
    }

    ASSERT_EQ(x_parallel, x_no_parallel);
    ASSERT_EQ(y_parallel, y_no_parallel);
}

TEST(test_tkachev_a_graham_pass, test_m1_1_1000) {
    const uint64_t SIZE = 100;
    const int FROM = -500;
    const int TO = 500;

    std::vector<Point> const points =
            getRandomizedVector(FROM, TO, SIZE);

    std::stack<Point> not_parallel =
            useGrahamAlgorithm(points, false);

    std::stack<Point> parallel =
            useGrahamAlgorithm(points, true);

    std::vector<double> x_no_parallel(not_parallel.size()),
                        y_no_parallel(not_parallel.size());

    for (std::size_t i = 0; !not_parallel.empty() &&
                        i < x_no_parallel.size(); i++) {
        x_no_parallel[i] = not_parallel.top().x;
        y_no_parallel[i] = not_parallel.top().y;
        not_parallel.pop();
    }

    std::vector<double> x_parallel(parallel.size()),
                        y_parallel(parallel.size());
    for (std::size_t i = 0; !parallel.empty() &&
                        i < x_parallel.size(); i++) {
        x_parallel[i] = parallel.top().x;
        y_parallel[i] = parallel.top().y;
        parallel.pop();
    }

    ASSERT_EQ(x_parallel, x_no_parallel);
    ASSERT_EQ(y_parallel, y_no_parallel);
}

TEST(test_tkachev_a_graham_pass, test_m5_5_10) {
    const uint64_t SIZE = 10;
    const int FROM = -5;
    const int TO = 5;

    std::vector<Point> const points =
            getRandomizedVector(FROM, TO, SIZE);

    std::stack<Point> not_parallel =
            useGrahamAlgorithm(points, false);

    std::stack<Point> parallel =
            useGrahamAlgorithm(points, true);

    std::vector<double> x_no_parallel(not_parallel.size()),
                        y_no_parallel(not_parallel.size());

    for (std::size_t i = 0; !not_parallel.empty() &&
                        i < x_no_parallel.size(); i++) {
        x_no_parallel[i] = not_parallel.top().x;
        y_no_parallel[i] = not_parallel.top().y;
        not_parallel.pop();
    }

    std::vector<double> x_parallel(parallel.size()),
                        y_parallel(parallel.size());
    for (std::size_t i = 0; !parallel.empty() &&
                        i < x_parallel.size(); i++) {
        x_parallel[i] = parallel.top().x;
        y_parallel[i] = parallel.top().y;
        parallel.pop();
    }

    ASSERT_EQ(x_parallel, x_no_parallel);
    ASSERT_EQ(y_parallel, y_no_parallel);
}

TEST(test_tkachev_a_graham_pass, test_m1_1_4) {
    const uint64_t SIZE = 4;
    const int FROM = -1;
    const int TO = 1;

    std::vector<Point> const points =
            getRandomizedVector(FROM, TO, SIZE);

    std::stack<Point> not_parallel =
            useGrahamAlgorithm(points, false);

    std::stack<Point> parallel =
            useGrahamAlgorithm(points, true);

    std::vector<double> x_no_parallel(not_parallel.size()),
                        y_no_parallel(not_parallel.size());

    for (std::size_t i = 0; !not_parallel.empty() &&
                        i < x_no_parallel.size(); i++) {
        x_no_parallel[i] = not_parallel.top().x;
        y_no_parallel[i] = not_parallel.top().y;
        not_parallel.pop();
    }

    std::vector<double> x_parallel(parallel.size()),
                        y_parallel(parallel.size());
    for (std::size_t i = 0; !parallel.empty() &&
                        i < x_parallel.size(); i++) {
        x_parallel[i] = parallel.top().x;
        y_parallel[i] = parallel.top().y;
        parallel.pop();
    }

    ASSERT_EQ(x_parallel, x_no_parallel);
    ASSERT_EQ(y_parallel, y_no_parallel);
}

TEST(test_tkachev_a_graham_pass, test_m100_100_3) {
    const uint64_t SIZE = 3;
    const int FROM = -100;
    const int TO = 100;

    std::vector<Point> const points =
            getRandomizedVector(FROM, TO, SIZE);

    std::stack<Point> not_parallel =
            useGrahamAlgorithm(points, false);

    std::stack<Point> parallel =
            useGrahamAlgorithm(points, true);

    std::vector<double> x_no_parallel(not_parallel.size()),
                        y_no_parallel(not_parallel.size());

    for (std::size_t i = 0; !not_parallel.empty() &&
                        i < x_no_parallel.size(); i++) {
        x_no_parallel[i] = not_parallel.top().x;
        y_no_parallel[i] = not_parallel.top().y;
        not_parallel.pop();
    }

    std::vector<double> x_parallel(parallel.size()),
                        y_parallel(parallel.size());
    for (std::size_t i = 0; !parallel.empty() &&
                        i < x_parallel.size(); i++) {
        x_parallel[i] = parallel.top().x;
        y_parallel[i] = parallel.top().y;
        parallel.pop();
    }

    ASSERT_EQ(x_parallel, x_no_parallel);
    ASSERT_EQ(y_parallel, y_no_parallel);
}

TEST(test_tkachev_a_graham_pass, test_m150_250_2) {
    const uint64_t SIZE = 2;
    const int FROM = -150;
    const int TO = 250;

    std::vector<Point> const points =
            getRandomizedVector(FROM, TO, SIZE);

    std::stack<Point> not_parallel =
            useGrahamAlgorithm(points, false);

    std::stack<Point> parallel =
            useGrahamAlgorithm(points, true);

    std::vector<double> x_no_parallel(not_parallel.size()),
                        y_no_parallel(not_parallel.size());

    for (std::size_t i = 0; !not_parallel.empty() &&
                        i < x_no_parallel.size(); i++) {
        x_no_parallel[i] = not_parallel.top().x;
        y_no_parallel[i] = not_parallel.top().y;
        not_parallel.pop();
    }

    std::vector<double> x_parallel(parallel.size()),
                        y_parallel(parallel.size());
    for (std::size_t i = 0; !parallel.empty() &&
                        i < x_parallel.size(); i++) {
        x_parallel[i] = parallel.top().x;
        y_parallel[i] = parallel.top().y;
        parallel.pop();
    }

    ASSERT_EQ(x_parallel, x_no_parallel);
    ASSERT_EQ(y_parallel, y_no_parallel);
}

TEST(test_tkachev_a_graham_pass, test_m10_30_1) {
    const uint64_t SIZE = 1;
    const int FROM = -10;
    const int TO = 30;

    std::vector<Point> const points =
            getRandomizedVector(FROM, TO, SIZE);

    std::stack<Point> not_parallel =
            useGrahamAlgorithm(points, false);

    std::stack<Point> parallel =
            useGrahamAlgorithm(points, true);

    std::vector<double> x_no_parallel(not_parallel.size()),
                        y_no_parallel(not_parallel.size());

    for (std::size_t i = 0; !not_parallel.empty() &&
                        i < x_no_parallel.size(); i++) {
        x_no_parallel[i] = not_parallel.top().x;
        y_no_parallel[i] = not_parallel.top().y;
        not_parallel.pop();
    }

    std::vector<double> x_parallel(parallel.size()),
                        y_parallel(parallel.size());
    for (std::size_t i = 0; !parallel.empty() &&
                        i < x_parallel.size(); i++) {
        x_parallel[i] = parallel.top().x;
        y_parallel[i] = parallel.top().y;
        parallel.pop();
    }

    ASSERT_EQ(x_parallel, x_no_parallel);
    ASSERT_EQ(y_parallel, y_no_parallel);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
