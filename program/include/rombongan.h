#ifndef rombongan
#define rombongan

#include "entity.h"
#include <vector>
#include <set>

struct Rombongan {
    std::vector<int> members;
    std::vector<std::pair<double, double> > time_list;
};

std::vector<Rombongan> identifyRombongan(
    const std::vector<Entity>& entities,
    int m,
    int k,
    double r,
    double cs
);

#endif