#include "entity.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

/**
 * Read data from a text file and return it as list of moving
 * entities
 * 
 * @param name Name of the file to be read from
 * @return List of moving entities with their trajectories
 */
std::vector<Entity> readMovementData(std::string name, std::string path) {
    std::ifstream file;
    std::string line;

    double frame_time;
    double id, x_pos, y_pos;

    std::string filepath = path + "/" + name + ".txt";

    std::cout << "Attempting to read data from: " << filepath << "\n"; 

    file.open(filepath);

    if (!file) {
        throw std::invalid_argument("File doesn't exist!");
    }

    std::map<int, std::map<double, std::vector<double> > > data_map;

    while (std::getline(file, line)) {
        std::stringstream line_stream(line);

        line_stream >> frame_time >> id >> x_pos;

        line_stream.ignore();

        line_stream >> y_pos;

        data_map[id][frame_time] = { x_pos, y_pos }; 
    }

    file.close();

    std::vector<Entity> result;

    for (auto const& entry: data_map) {
        int id = entry.first;
        std::map<double, std::vector<double> > frame_position = entry.second;

        std::vector<std::vector<double> > trajectory;

        for (auto const& position: frame_position) {
            trajectory.push_back(position.second);
        }

        result.push_back({ id, trajectory });
    }

    return result;
}
