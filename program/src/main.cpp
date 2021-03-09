#include "io.h"
#include "parser.h"
#include "rombongan.h"
#include <algorithm>
#include <chrono>
#include <iostream>

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    Parameters args = parseArguments(argc, argv);
    auto entities = parseMovementData(
        args.source,
        args.path
    );

    std::cout << "Number of entities: " << entities.size() << std::endl;
    std::cout << "Number of frames: " << entities[0].trajectories.size() << std::endl;

    auto result = identifyRombongan(
        entities,
        args.entity_count,
        args.time_interval,
        args.range,
        args.cosine_similarity
    );

    auto end = std::chrono::high_resolution_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Succesfully identified " << result.size() << " rombongan(s) from the current dataset" << std::endl;
    std::cout << "Runtime: " << millis.count() << " ms." << std::endl;

    writeResultToFile(result, args.source);

    return 0;
}