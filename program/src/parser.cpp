#include "entity.h"
#include "io.h"
#include "parser.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <filesystem>
#include <map>
#include <stdexcept>

const double PI = std::acos(-1);

typedef std::map<double, std::unordered_map<unsigned int, std::vector<double> > > frame_to_entity;
typedef std::unordered_map<unsigned int, std::vector<std::vector<double> > > entity_to_frame;

/**
 * Parse data from a text file and return it as list of moving
 * entities
 * 
 * @param name Name of the file to be read from
 * @param path File path to read from
 * @return List of moving entities with their trajectories
 */
MovementData parse_data(
    const std::string& name,
    const std::string& path
) {
    std::ifstream file;
    std::string line;

    double frame_time, id, x_pos, y_pos;

    auto filepath = (std::filesystem::path(path) / "input" / name)
        .make_preferred()
        .replace_extension(".txt");

    std::cout << "Attempting to read source data from: ";
    std::cout << filepath.string() << std::endl; 

    file.open(filepath);

    if (!file) {
        throw std::invalid_argument("Source data doesn't exist!");
    }

    std::unordered_set<unsigned int> id_frame;
    std::unordered_set<unsigned int> id_list;

    frame_to_entity data_map;
    entity_to_frame trajectory_map;

    while (std::getline(file, line)) {
        std::istringstream line_stream(line);

        line_stream >> frame_time >> id >> x_pos >> y_pos >> y_pos;

        id_list.insert(id);

        data_map[frame_time][id] = { x_pos, y_pos }; 
    }

    file.close();

    std::vector<double> frames;

    for (auto const& [frame, position]: data_map) {
        frames.push_back(frame);
    
        for (auto const& [id, plane]: position) {
            trajectory_map[id].push_back(
                plane  
            );

            id_frame.insert(id);
        }

        for (auto const id: id_list) {
            if (id_frame.find(id) == id_frame.end()) {
                trajectory_map[id].push_back({ -1, -1 });
            }
        }

        id_frame.clear();
    }

    std::vector<Entity> entities;

    for (auto const& [id, frame]: trajectory_map) {
        entities.push_back(
            { id, frame }
        );
    }

    // make sure that entities are sorted to prevent random pairings
    sort(entities.begin(), entities.end());

    return {
        entities,
        frames
    };
}

/**
 * Parse rombongan identification parameters from input
 * arguments
 * 
 * @param args input arguments
 * @return rombongan identification parameters
 */
Parameter parse_arguments(
    const Arguments& args
) {
    Parameter params;

    params.m = args.entities;
    params.k = round(args.interval * args.fps);
    params.r = args.range * args.interval * args.fps;
    params.cs = cos(args.angle * PI / 180);
    params.p = ceil(args.fps);

    return params;
}

/**
 * Parse expected result from a text file and return it
 * as an array of entity id
 * 
 * @param name expected result filename
 * @param path expected result filepath
 * 
 * @return list of groups, which is a list of id
 */
std::vector<std::vector<unsigned int> > parse_expected_result(
    const std::string& name,
    const std::string& path
) {
    std::ifstream file;
    std::string line;
    unsigned int bucket;

    double frame_time, id, x_pos, y_pos;

    auto filepath = (std::filesystem::path(path) / "result" / name)
        .make_preferred()
        .replace_extension(".txt");

    std::cout << "Attempting to read expected results from: ";
    std::cout << filepath.string() << std::endl; 

    file.open(filepath);

    if (!file) {
        throw std::invalid_argument("Expected result doesn't exist!");
    }

    std::vector<std::vector<unsigned int> > expected_result;

    while (std::getline(file, line)) {
        std::vector<unsigned int> group;

        std::istringstream line_stream(line);

        while (line_stream >> bucket) {
            group.push_back(bucket);
        }

        // sort the ids to make sure that default
        // comparator function work.
        sort(group.begin(), group.end());

        expected_result.push_back(group);
    }

    return expected_result;
}
