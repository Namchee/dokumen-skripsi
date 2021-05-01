#ifndef parser
#define parser

#include "entity.h"
#include <vector>
#include <string>

class MovementData {
public:
    std::vector<Entity> entities;
    std::vector<double> frames;
};

class Parameter {
public:
    unsigned int m, k, p;
    double r, cs;
};

class Arguments;

MovementData parse_data(const std::string&, const std::string&);
Parameter parse_arguments(const Arguments&);
std::vector<std::vector<unsigned int> > parse_expected_result(
    const std::string&,
    const std::string&
);

#endif
