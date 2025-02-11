// Copyright 2021 Zoreev Mikhail

#include "../../../modules/task_1/zoreev_m_trapezoidal_rule/trapezoidal_rule.h"

double integrate(const std::function<double(std::vector<double>)>& f,
    const std::vector<double>& from, const std::vector<double>& to,
    uint64_t steps) {
    if (steps == 0) {
        throw std::runtime_error("Wrong steps count");
    }
    if (from.size() != to.size()) {
        throw std::runtime_error("Wrong range");
    }
    if (from.empty() || to.empty()) {
        throw std::runtime_error("Range is empty");
    }

    double block_size = 1;
    size_t blocks_count = 1;
    std::vector<double> deltas(from.size());
    std::vector<size_t>dimension_divider(from.size());

    for (size_t i = 0; i < from.size(); i++) {
        deltas[i] = (to[i] - from[i]) / static_cast<double>(steps);
        block_size *= deltas[i];
        dimension_divider[i] = blocks_count;
        blocks_count *= steps;
    }

    double result = 0.0;
    std::vector<double> block_coordinates(from.size());
    for (size_t i = 1; i < blocks_count - 1; i++) {
        for (size_t j = 0; j < from.size(); j++) {
            block_coordinates[j] = from[j] + (i / dimension_divider[j] % steps)
                * deltas[j];
        }
        result += f(block_coordinates);
    }
    result += (f(from) + f(to)) / 2;
    result *= block_size;
    return result;
}
