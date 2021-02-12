#ifndef parser
#define parser

#include "entity.h"
#include <vector>
#include <string>

std::vector<Entity> parseMovementData(const std::string& name, const std::string& path);

#endif
