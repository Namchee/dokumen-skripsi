#include "entity.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <stdexcept>

/**
 * Read data from a text file and return it as list of moving
 * entities
 * 
 * @param name Name of the file to be read from
 * @return List of moving entities with their trajectories
 */
std::vector<Entity> parseMovementData(const std::string& name, const std::string& path) {
    std::ifstream file;
    std::string line;

    double frame_time, id, x_pos, y_pos;

    std::string filepath = path + "/" + name + ".txt";

    std::cout << "Attempting to read data from: " << filepath << "\n"; 

    file.open(filepath);

    if (!file) {
        throw std::invalid_argument("File doesn't exist!");
    }

    std::unordered_set<int> id_frame;
    std::unordered_set<int> id_list;

    std::map<double, std::unordered_map<int, std::vector<double> > > data_map;
    std::unordered_map<int, std::map<double, std::vector<double> > > trajectory_map;

    while (std::getline(file, line)) {
        std::istringstream line_stream(line);

        line_stream >> frame_time >> id >> x_pos >> y_pos >> y_pos;

        id_list.insert(id);

        data_map[frame_time][id] = { x_pos, y_pos }; 
    }

    file.close();

    for (auto const& [frame, position]: data_map) {
        for (auto const& [id, plane]: position) {
            trajectory_map[id][frame] = plane;
            id_frame.insert(id);
        }

        for (auto id: id_list) {
            if (id_frame.find(id) == id_frame.end()) {
                trajectory_map[id][frame] =
                    {
                        std::numeric_limits<double>::max(),
                        std::numeric_limits<double>::max()
                    };
            }
        }

        id_frame.clear();
    }

    std::vector<Entity> result;

    for (auto const& [id, frame]: trajectory_map) {
        result.push_back(
            { id, frame }
        );
    }

    return result;
}
