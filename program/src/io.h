#ifndef io
#define io

#include <vector>
#include <string>

class Rombongan;
class Score;

/**
 * Parameters to be used when identifying rombongan from trajectory data.
 */
class Arguments {
public:
    std::string source;
    std::string path;
    unsigned int entities;
    double interval;
    double range;
    double angle;
    double fps;
};

Arguments read_arguments(int, char *[]);

void write_result(
    const std::vector<Rombongan>&,
    const std::vector<double>&,
    const Arguments&,
    const Score&
);

#endif