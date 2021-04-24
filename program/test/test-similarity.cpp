#include "similarity.h"
#include <vector>
#include <cassert>
#include <stdexcept>
#include <iostream>

// Sample test case, stolen from internet
void dtw_should_return_correct_value() {
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

    double range = calculate_dtw_distance(a, b);

    assert(range == 2.0f);
}

// Another sample test case, stolen from internet
void dtw_should_also_return_correct_value() {
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

    double range = calculate_dtw_distance(a, b);

    assert(range == 6.0f);
}

// Input order shouldn't matter
void dtw_should_return_correct_value_as_input_order_does_not_matter() {
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

    double range = calculate_dtw_distance(a, b);

    assert(range == 2.0f);
}

// Throw length_error when dimension is not same
void dtw_should_throw_error_when_dimension_is_not_same() {
    std::vector<std::vector<double> > a = {
        { 1 }
    };

    std::vector<std::vector<double> > b = {
        { 1, 2 }
    };

    try {
        calculate_dtw_distance(a, b);

        throw std::logic_error("Should throw an error as trajectories reside in different movement dimension.");
    } catch(std::invalid_argument const &err) {
        assert(err.what() == std::string("Both trajectories must reside in the same dimensional space."));
    }
}

void dtw_should_throw_error_when_trajectory_is_empty() {
    std::vector<std::vector<double> > a = {};

    std::vector<std::vector<double> > b = {
        { 1, 2 }
    };

    try {
        calculate_dtw_distance(a, b);

        throw std::logic_error("Should throw an error as trajectory `a` is empty");
    } catch(std::invalid_argument const &err) {
        assert(err.what() == std::string("Both trajectories must not be empty."));
    }
}

void cosine_should_return_correct_value() {
    std::vector<double> a = { 3, 2, 0, 5 };
    std::vector<double> b = { 1, 0, 0, 0 };

    double cosine_similarity = calculate_cosine_similarity(a, b);

    assert(abs(cosine_similarity - 0.49) < 1e-9); 
}

void cosine_should_throw_an_error_when_dimension_is_not_same() {
    std::vector<double> a = { 3 };
    std::vector<double> b = { 3, 1 };

    try {
        calculate_cosine_similarity(a, b);

        throw std::logic_error(
            "Should throw an error as vectors does not reside in the same dimensional space."
        );
    } catch(std::invalid_argument const &err) {
        assert(
            err.what() == std::string("Both vector must reside in the same dimensional space.")
        );
    }
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        throw std::invalid_argument("This test file requires an argument.");
    }

    std::string cmd(argv[1]);

    if (cmd == "dtw") {
        dtw_should_return_correct_value();
        dtw_should_also_return_correct_value();
        dtw_should_return_correct_value_as_input_order_does_not_matter();
        dtw_should_throw_error_when_dimension_is_not_same();
        dtw_should_throw_error_when_trajectory_is_empty();
    } else {
        cosine_should_return_correct_value();
        cosine_should_throw_an_error_when_dimension_is_not_same();
    }

    return 0;
}
