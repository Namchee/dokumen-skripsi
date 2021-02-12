#include "dtw.h"
#include <vector>
#include <cassert>
#include <stdexcept>
#include <iostream>

// Sample test case, stolen from internet
void should_return_correct_vaue() {
    std::vector<std::vector<double> > a = {
        { 1 },
        { 2 },
        { 3 },
    };

    std::vector<std::vector<double> > b = {
        { 2 },
        { 2 },
        { 2 },
        { 3 },
        { 4 }
    };

    double range = calculateDTWDistance(a, b);

    assert(range == 2.0f);
}

// Another sample test case, stolen from internet
void should_also_return_correct_value() {
    std::vector<std::vector<double> > a = {
        { 3 },
        { 1 },
        { 2 },
        { 2 },
        { 1 }
    };

    std::vector<std::vector<double> > b = {
        { 2 },
        { 0 },
        { 0 },
        { 3 },
        { 3 },
        { 1 },
        { 0 }
    };

    double range = calculateDTWDistance(a, b);

    assert(range == 6.0f);
}

// Input order shouldn't matter
void should_return_correct_value_as_input_order_does_not_matter() {
    std::vector<std::vector<double> > b = {
        { 1 },
        { 2 },
        { 3 },
    };

    std::vector<std::vector<double> > a = {
        { 2 },
        { 2 },
        { 2 },
        { 3 },
        { 4 }
    };

    double range = calculateDTWDistance(a, b);

    assert(range == 2.0f);
}

// Throw length_error when dimension is not same
void should_throw_error_when_dimension_is_not_same() {
    std::vector<std::vector<double> > a = {
        { 1 }
    };

    std::vector<std::vector<double> > b = {
        { 1, 2 }
    };

    try {
        calculateDTWDistance(a, b);

        throw std::logic_error("Should throw an error as trajectories reside in different movement dimension.");
    } catch(std::invalid_argument const &err) {
        assert(err.what() == std::string("Both trajectories must reside in the same dimensional space."));
    }
}

void should_throw_error_when_trajectory_is_empty() {
    std::vector<std::vector<double> > a = {};

    std::vector<std::vector<double> > b = {
        { 1, 2 }
    };

    try {
        calculateDTWDistance(a, b);

        throw std::logic_error("Should throw an error as trajectory `a` is empty");
    } catch(std::invalid_argument const &err) {
        assert(err.what() == std::string("Both trajectories must not be empty."));
    }
}

int main() {
    should_return_correct_vaue();
    should_also_return_correct_value();
    should_return_correct_value_as_input_order_does_not_matter();
    should_throw_error_when_dimension_is_not_same();
    should_throw_error_when_trajectory_is_empty();

    return 0;
}
