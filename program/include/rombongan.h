#ifndef rombongan
#define rombongan

#include "entity.h"
#include <vector>
#include <set>

struct Rombongan {
    std::vector<int> members;
    double start, end;
};

std::vector<Rombongan> identifyRombongan(
    std::vector<Entity> entities,
    int m,
    int k,
    double r,
    double cs
);

#endif