#include "io.h"
#include "utils.h"
#include "parser.h"
#include "eval.h"
#include "rombongan.h"
#include <iostream>

int main(int argc, char *argv[]) {
    auto start = get_current_time();

    Arguments arguments = read_arguments(argc, argv);

    auto [entities, frames] = parse_data(
        arguments.source,
        arguments.path
    );

    std::cout << "Number of entities: ";
    std::cout << entities.size() << " entities" << std::endl;
    std::cout << "Number of frames: ";
    std::cout << entities[0].trajectories.size() << " frames" << std::endl;

    Parameter params = parse_arguments(arguments);

    auto rombongan_list = identify_rombongan(
        entities,
        params
    );

    auto end = get_current_time();
    auto delta = end - start; 

    std::cout << "Succesfully identified ";
    std::cout << rombongan_list.size();
    std::cout << " rombongan(s) from the current dataset" << std::endl;
    std::cout << "Runtime: " << std::to_string(delta) << " ms." << std::endl;

    auto expected_result = parse_expected_result(
        arguments.source,
        arguments.path
    );

    Score identification_score = calculate_score(expected_result, rombongan_list);

    write_result(
        rombongan_list,
        frames,
        arguments,
        identification_score
    );

    return 0;
}