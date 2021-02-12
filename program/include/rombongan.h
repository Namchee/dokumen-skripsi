#ifndef rombongan
#define rombongan

#include "entity.h"
#include <vector>
#include <unordered_set>

std::vector<std::vector<std::unordered_set<int> > > identifyRombongan(
    const std::vector<Entity>& entities,
    int m,
    int k,
    double r,
    double cs
);

#endif