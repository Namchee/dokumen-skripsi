#ifndef entity
#define entity

#include <vector>

struct Entity {
    int id;
    std::vector<std::vector<double> > trajectories;

    bool operator<(const Entity &o) {
        return id < o.id;
    }
};

#endif