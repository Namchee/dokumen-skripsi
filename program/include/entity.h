#ifndef entity
#define entity

#include <vector>

struct Entity {
    int id;
    std::vector<std::vector<int> > trajectories;
};

#endif