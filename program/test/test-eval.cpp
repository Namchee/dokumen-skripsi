#include "eval.h"
#include "rombongan.h"
#include <vector>
#include <cmath>
#include <cassert>

std::vector<std::vector<unsigned int> > expected_result = {
    { 1 },
    { 2 },
    { 3 },
    { 4 },
    { 5 },
    { 7 },
    { 8 },
};

std::vector<Rombongan> result = {
    { { 1 }, {} },
    { { 2 }, {} },
    { { 3 }, {} },
    { { 4 }, {} },
    { { 5 }, {} },
    { { 6 }, {} }
};

int main() {
    auto [precision, recall, f1_score] = calculate_score(
        expected_result,
        result
    );

    assert(abs(precision - 0.833) < 10e-6);
    assert(abs(recall - 0.714) < 10e-6);
    assert(abs(f1_score - 0.769) < 10e-6);

    return 0;
}