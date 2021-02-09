#include "dtw.h"
#include <vector>
#include <cassert>
#include <iostream>

int main() {
    std::vector<std::vector<int> > a = {
        { 3 },
        { 1 },
        { 2 },
        { 2 },
        { 1 },
    };

    std::vector<std::vector<int> > b = {
        { 2 },
        { 0 },
        { 0 },
        { 3 },
        { 3 },
        { 1 },
        { 0 },
    };

    double range = calculateDTWDistance(a, b);

    assert(range == 6.0f);

    return 0;
}
