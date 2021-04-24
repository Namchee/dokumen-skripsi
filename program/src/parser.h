#ifndef parser
#define parser

#include "entity.h"
#include <vector>
#include <string>

std::vector<Entity> parse_data(const std::string&, const std::string&);
std::vector<std::vector<unsigned int> > parse_expected_result(
    const std::string&,
    const std::string&
);

#endif
