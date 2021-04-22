#include "io.h"
#include "utils.h"
#include "parser.h"
#include "rombongan.h"
#include <iostream>

int main(int argc, char *argv[]) {
    auto start = get_current_time();

    Parameters arguments = parseArguments(argc, argv);
    auto entities = parseMovementData(
        arguments.source,
        arguments.path
    );

    std::cout << "Number of entities: " << entities.size() << std::endl;
    std::cout << "Number of frames: " << entities[0].trajectories.size() << std::endl;

    auto result = identifyRombongan(
        entities,
        arguments
    );

    auto end = get_current_time();
    auto delta = end - start; 

    std::cout << "Succesfully identified ";
    std::cout << result.size();
    std::cout << " rombongan(s) from the current dataset" << std::endl;
    std::cout << "Runtime: " << std::to_string(delta) << " ms." << std::endl;

    writeResultToFile(result, arguments);

    return 0;
}