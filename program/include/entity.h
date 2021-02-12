#ifndef entity
#define entity

#include <vector>

struct Entity {
    int id;
    std::vector<std::vector<double> > trajectories;

    bool operator<(const Entity &o) const {
        return id < o.id;
    }

    bool operator==(const Entity &o) const {
        return id == o.id;
    }
};

class EntityHasher {
public:
    size_t operator()(const Entity &e) const {
        return e.id;
    }
};

#endif