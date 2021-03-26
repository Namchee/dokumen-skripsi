#include "rombongan.h"
#include "similarity.h"
#include "entity.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <iostream>

/**
 * Identify rombongan from a set of moving entities.
 * 
 * @param entities - list of moving entities in two-dimensional space
 */
std::vector<Rombongan> identifyRombongan(
    const std::vector<Entity>& entities,
    int m,
    int k,
    double r,
    double cs
) {
    std::map<std::vector<int>, std::vector<std::pair<double, double> > > paired_groups;
    std::vector<double> frames;

    for (auto x: entities[0].trajectories) {
        frames.push_back(x.first);
    }

    unsigned int dimension = (*entities[0].trajectories.begin()).second.size();

    for (size_t end = k; end < frames.size(); end++) {
        if (end > 50) {
            break;
        }    

        unsigned int start = end - k;

        std::vector<std::vector<int> > rombongan_group;
        std::unordered_map<int, std::vector<std::vector<double> > > sub_trajectories;
        std::unordered_map<int, std::vector<double> > direction_vector;

        // cache the sub-trajectories and direction vector
        for (size_t it = 0; it < entities.size(); it++) {
            Entity curr = entities[it];

            for (size_t frame = start; frame < end; frame++) {
                sub_trajectories[curr.id].push_back(
                    curr.trajectories[frames[frame]]
                );
            }

            for (size_t dim = 0; dim < dimension; dim++) {
                direction_vector[curr.id].push_back(
                    curr.trajectories[frames[end - 1]][dim] - curr.trajectories[frames[start]][dim]
                );
            }
        }

        for (size_t curr_itr = 0; curr_itr < entities.size(); curr_itr++) {
            Entity curr = entities[curr_itr];
            std::vector<std::vector<int> > group_ids;

            for (size_t other_itr = curr_itr + 1; other_itr < entities.size(); other_itr++) {
                Entity other = entities[other_itr];

                for (size_t groups_itr = 0; groups_itr < group_ids.size(); groups_itr++) {
                    bool is_similar_to_all_members = true;

                    for (int member_id: group_ids[groups_itr]) {
                        double dtw_distance = calculateDTWDistance(
                            sub_trajectories[other.id],
                            sub_trajectories[member_id]
                        );

                        double cosine_similarity = calculateCosineSimilarity(
                            direction_vector[other.id],
                            direction_vector[member_id]
                        );

                        // make sure that the distance is not zero to avoid
                        // similarity checking when two entities
                        // doesn't appear in the current timeframe.
                        is_similar_to_all_members = member_id != other.id && 
                            dtw_distance != -1 &&
                            dtw_distance <= r &&
                            cosine_similarity >= cs;

                        if (!is_similar_to_all_members) {
                            break;
                        }
                    }

                    if (is_similar_to_all_members) {
                        std::vector new_group = std::vector<int>(
                            group_ids[groups_itr].begin(),
                            group_ids[groups_itr].end()
                        );

                        new_group.push_back(other.id);
                        group_ids.push_back(new_group);
                    }
                }

                // can entity `curr` create a subgroup with `other`?
                double dtw_distance = calculateDTWDistance(
                    sub_trajectories[other.id],
                    sub_trajectories[curr.id]
                );

                double cosine_similarity = calculateCosineSimilarity(
                    direction_vector[other.id],
                    direction_vector[curr.id]
                );

                if (dtw_distance != -1 && dtw_distance <= r && cosine_similarity >= cs) {
                    group_ids.push_back({ curr.id, other.id });
                }
            }

            for (size_t itr_group = 0; itr_group < group_ids.size(); itr_group++) {
                rombongan_group.push_back(group_ids[itr_group]);
            }
        }

        for (std::vector<int> group: rombongan_group) {
            std::vector<std::pair<double, double> > time_list = paired_groups[group];

            if (
                time_list.size() == 0 ||
                start == 0 ||
                frames[end - 1] != time_list[time_list.size() - 1].second
            ) {
                paired_groups[group].push_back({ frames[start], frames[end] });
            } else {
                paired_groups[group][time_list.size() - 1] = { 
                    paired_groups[group][time_list.size() - 1].first,
                    frames[end]
                };
            }
        }

        std::cout << "Finished processing range [" << start << ", " << end << "]" << std::endl;
    }

    std::vector<Rombongan> raw_result;

    for (auto const& [group, duration]: paired_groups) {
        raw_result.push_back({
            group,
            duration
        });
    }

    return raw_result;
}
