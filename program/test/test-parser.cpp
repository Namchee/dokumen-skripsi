#include "parser.h"
#include "entity.h"
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <stdexcept>

std::vector<std::vector<double> > b_trajectory{
    { std::numeric_limits<double>::max(), std::numeric_limits<double>::max() },
    { std::numeric_limits<double>::max(), std::numeric_limits<double>::max() },
    { 1.5, 1.5 },
    { std::numeric_limits<double>::max(), std::numeric_limits<double>::max() }
};

std::vector<std::vector<double> > a_trajectory{
    { 1.0, 1.0 },
    { 2.0, 2.0 },
    { std::numeric_limits<double>::max(), std::numeric_limits<double>::max() },
    { 3.0, 5.55 }
};

void should_parse_correctly() {
    std::string source("test_data");
    std::string path("test/fixtures");

    std::vector<Entity> entities = parseMovementData(source, path);

    for (unsigned int i = 0; i < entities.size(); i++) {
        Entity curr = entities[i];
        std::vector<std::vector<double> > traj = curr.trajectories;

        std::cout << curr.id << std::endl;

        if (curr.id == 2) {
            for (unsigned int j = 0; j < (int)b_trajectory.size(); j++) {
                assert(curr.trajectories[j][0] == b_trajectory[j][0]);
                assert(curr.trajectories[j][1] == b_trajectory[j][1]);
            }
        } else {
            for (unsigned int j = 0; j < (int)a_trajectory.size(); j++) {
                assert(curr.trajectories[j][0] == a_trajectory[j][0]);
                assert(curr.trajectories[j][1] == a_trajectory[j][1]);
            }
        }
    }
}

void should_throw_an_error_as_file_not_found() {
    std::string source("not_exist");
    std::string path("test/fixtures");

    try {
        parseMovementData(source, path);
        throw std::logic_error("Should throw an error as file does not exist.");
    } catch(const std::invalid_argument &err) {
        assert(err.what() == std::string("File doesn't exist!"));
    }
}

int main() {
    should_parse_correctly();
    should_throw_an_error_as_file_not_found();

    return 0;
}