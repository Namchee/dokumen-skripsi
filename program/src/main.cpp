#include "io.h"
#include "parser.h"
#include "rombongan.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Parameters args = parseArguments(argc, argv);
    auto entities = parseMovementData(
        args.source,
        args.path
    );

    auto result = identifyRombongan(
        entities,
        args.entity_count,
        args.time_interval,
        args.range,
        args.cosine_similarity
    );

    writeResultToFile(result, args.source);

    return 0;
}