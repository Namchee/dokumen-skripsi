#ifndef eval
#define eval

#include "rombongan.h"
#include <vector>

class Score {
public:
    double precision, recall, f1_score;
};

Score calculate_score(
    const std::vector<std::vector<unsigned int> >&,
    const std::vector<Rombongan>&
);

#endif
