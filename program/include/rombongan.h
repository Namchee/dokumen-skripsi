#ifndef rombongan
#define rombongan

#include "io.h"
#include "entity.h"
#include <vector>

class Parameters;

class Rombongan {
public:
    std::vector<unsigned int> members;
    std::vector<std::pair<double, double> > duration;

    bool operator<(const Rombongan& other) const {
        return members.size() > other.members.size();
    }
};

std::vector<Rombongan> identify_rombongan(
    const std::vector<Entity>& entities,
    const Parameters& params
);

#endif