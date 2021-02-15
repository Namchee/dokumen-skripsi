#include "rombongan.h"
#include "similarity.h"
#include "entity.h"
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>

/**
 * Identify rombongan from a set of moving entities.
 * 
 * @param entities - list of moving entities in two-dimensional space
 */
std::vector<Rombongan> identifyRombongan(
    std::vector<Entity> entities,
    int m,
    int k,
    double r,
    double cs
) {
    std::map<std::vector<int>, std::pair<double, double> > paired_groups;
    std::vector<double> frames;
    unsigned int dimension;

    for (auto x: entities[0].trajectories) {
        frames.push_back(x.first);
        dimension = x.second.size();
    }

    for (unsigned int end = k; end < frames.size(); end++) {
        if (end == 100) {
            break;
        }

        unsigned int start = end - k;

        std::vector<std::vector<int> > rombongan_group;
        std::unordered_map<int, std::vector<std::vector<double> > > sub_trajectories;
        std::unordered_map<int, std::vector<double> > direction_vector;

        // cache the sub-trajectories and direction vector
        for (unsigned int it = 0; it < entities.size(); it++) {
            Entity curr = entities[it];

            for (unsigned int frame = start; frame < end; frame++) {
                sub_trajectories[curr.id].push_back(
                    curr.trajectories[frames[frame]]
                );
            }

            for (unsigned int dim = 0; dim < dimension; dim++) {
                direction_vector[curr.id].push_back(
                    curr.trajectories[frames[end - 1]][dim] - curr.trajectories[frames[start]][dim]
                );
            }
        }

        for (unsigned int itr_outer = 0; itr_outer < entities.size(); itr_outer++) {
            std::vector<int> group_id{ entities[itr_outer].id };

            for (unsigned int itr_inner = itr_outer + 1; itr_inner < entities.size(); itr_inner++) {
                Entity other = entities[itr_inner];

                bool is_similar_to_all = true;

                for (unsigned int group_itr = 0; group_itr < group_id.size() && is_similar_to_all; group_itr++) {
                    double dist = calculateDTWDistance(
                        sub_trajectories[other.id],
                        sub_trajectories[group_id[group_itr]]
                    );

                    double cosim = calculateCosineSimilarity(
                        direction_vector[other.id],
                        direction_vector[group_id[group_itr]]
                    );
                    
                    is_similar_to_all = calculateDTWDistance(
                        sub_trajectories[other.id],
                        sub_trajectories[group_id[group_itr]]
                    ) <= r &&
                        calculateCosineSimilarity(
                            direction_vector[other.id],
                            direction_vector[group_id[group_itr]]
                        ) >= cs;
                }

                if (is_similar_to_all) {
                    group_id.push_back(other.id);
                }
            }

            if (group_id.size() >= m) {
                rombongan_group.push_back(group_id);
            }
        }

        for (std::vector<int> group: rombongan_group) {
            if (paired_groups.find(group) == paired_groups.end()) {
                paired_groups[group].first = frames[start];
                paired_groups[group].second = frames[end - 1];
            } else {
                paired_groups[group].second = frames[end - 1];
            }
        }
    }

    std::vector<Rombongan> result;

    for (auto const& [group, duration]: paired_groups) {
        result.push_back({
            group,
            duration.first,
            duration.second
        });
    }

    return result;
}
