#ifndef entity
#define entity

#include <vector>

class Entity {
public:
    unsigned int id;
    std::vector<std::vector<double> > trajectories;

    bool operator<(const Entity& o) const {
        return id < o.id;
    }
};

#endif