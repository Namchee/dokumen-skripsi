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

    // test
    std::sort(entities.begin(), entities.end());

    entities = std::vector<Entity>(
        entities.begin(),
        entities.begin() + 20
    );

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