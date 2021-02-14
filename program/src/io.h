#ifndef io
#define io

#include "rombongan.h"
#include <vector>
#include <string>

/**
 * Parameters to be used when identifying rombongan from trajectory data.
 */
struct Parameters {
    std::string source;
    int entity_count;
    int time_interval;
    double range;
    double cosine_similarity;
    std::string path;
};

Parameters parseArguments(int argc, char *argv[]);
void writeResultToFile(const std::vector<Rombongan>& result);

#endif