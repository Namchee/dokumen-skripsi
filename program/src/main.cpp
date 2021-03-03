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

    std::cout << entities.size() << std::endl;
    std::cout << entities[0].trajectories.size() << std::endl;

    // test
    // std::sort(entities.begin(), entities.end());

    auto result = identifyRombongan(
        entities,
        args.entity_count,
        args.time_interval,
        args.range,
        args.cosine_similarity
    );

    std::cout << "Succesfully identified " << result.size() << " rombongan(s) from the current dataset" << std::endl;

    writeResultToFile(result, args.source);

    return 0;
}