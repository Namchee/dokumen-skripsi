#ifndef rombongan
#define rombongan

#include "entity.h"
#include <vector>
class Rombongan {
public:
    std::vector<unsigned int> members;
    std::vector<std::pair<unsigned int, unsigned int> > duration;

    bool operator<(const Rombongan& other) const {
        return members.size() > other.members.size();
    }
};

class Parameter;

std::vector<Rombongan> identify_rombongan(
    const std::vector<Entity>& entities,
    const Parameter& params
);

#endif