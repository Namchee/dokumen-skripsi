#include "eval.h"
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

std::vector<std::vector<unsigned int> > result = {
    { 1 },
    { 2 },
    { 3 },
    { 4 },
    { 5 },
    { 6 },
};

int main() {
    double f1_score = calculate_f1_score(expected_result, result);

    assert(abs(f1_score - 0.769) < 10e-6);

    return 0;
}