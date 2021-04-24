#ifndef io
#define io

#include "rombongan.h"
#include <vector>
#include <string>

class Rombongan;
class Score;

/**
 * Parameters to be used when identifying rombongan from trajectory data.
 */
class Parameters {
public:
    std::string source;
    int entity_count;
    int time_interval;
    double range;
    double cosine_similarity;
    double fps;
    std::string path;
};

Parameters read_arguments(int, char *[]);

void write_result(
    const std::vector<Rombongan>&,
    const Parameters&,
    const Score&
);

#endif