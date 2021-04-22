#ifndef entity
#define entity

#include <vector>
#include <map>

struct Entity {
    unsigned int id;
    std::map<double, std::vector<double> > trajectories;

    bool operator<(const Entity& o) const {
        return id < o.id;
    }
};

#endif