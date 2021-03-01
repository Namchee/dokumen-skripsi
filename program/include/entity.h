#ifndef entity
#define entity

#include <vector>
#include <map>

struct Entity {
    int id;
    std::map<double, std::vector<double> > trajectories;
};

#endif