#include "io.h"
#include "parser.h"
#include "rombongan.h"
#include <algorithm>
#include <iostream>

int main(int argc, char *argv[]) {
    Parameters args = parseArguments(argc, argv);
    auto entities = parseMovementData(
        args.source,
        args.path
    );

    std::sort(entities.begin(), entities.end());

    entities = std::vector<Entity>(
        entities.begin(),
        entities.begin() + 20
    );

    std::cout << "Entity count: " << entities.size() << std::endl;

    auto result = identifyRombongan(
        entities,
        args.entity_count,
        args.time_interval,
        args.range,
        args.cosine_similarity
    );

    std::cout << result.size() << std::endl;

    writeResultToFile(result, args.source);

    return 0;
}