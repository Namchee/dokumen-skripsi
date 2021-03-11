#include "rombongan.h"
#include "similarity.h"
#include "entity.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
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
    std::map<std::vector<int>, std::pair<double, double> > paired_groups;
    std::vector<double> frames;
    unsigned int dimension;

    for (auto x: entities[0].trajectories) {
        frames.push_back(x.first);
        dimension = x.second.size();
    }

    for (size_t end = k; end < frames.size(); end++) {
        if (end > 25) {
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

        for (size_t itr_outer = 0; itr_outer < entities.size(); itr_outer++) {
            Entity curr = entities[itr_outer];
            std::vector<std::vector<int> > group_ids;
            // std::vector<int> group_id{ entities[itr_outer].id };

            for (size_t itr_inner = itr_outer + 1; itr_inner < entities.size(); itr_inner++) {
                Entity other = entities[itr_inner];

                // check if an entity may extend existing group
                for (size_t itr_groups = 0; itr_groups < group_ids.size(); itr_groups++) {
                    bool is_similar_to_all = true;

                    for (size_t itr_group = 0; itr_group < group_ids[itr_groups].size(); itr_group++) {
                        double dtw_distance = calculateDTWDistance(
                            sub_trajectories[other.id],
                            sub_trajectories[group_ids[itr_groups][itr_group]]
                        );

                        double cosine_similarity = calculateCosineSimilarity(
                            direction_vector[other.id],
                            direction_vector[group_ids[itr_groups][itr_group]]
                        );

                        // make sure that the distance is not zero to avoid
                        // similarity checking when two entities
                        // doesn't appear in the current timeframe.
                        is_similar_to_all = dtw_distance != -1 && dtw_distance <= r &&
                            cosine_similarity >= cs;
                    }

                    if (is_similar_to_all) {
                        group_ids[itr_groups].push_back(other.id);
                    }
                }

                double dtw_distance = calculateDTWDistance(
                    sub_trajectories[other.id],
                    sub_trajectories[curr.id]
                );

                double cosine_similarity = calculateCosineSimilarity(
                    direction_vector[other.id],
                    direction_vector[curr.id]
                );

                if (dtw_distance != -1 && dtw_distance <= r && cosine_similarity <= cs) {
                    group_ids.push_back({ curr.id, other.id });
                }

                /*
                bool is_similar_to_all = true;

                for (size_t group_itr = 0; group_itr < group_id.size() && is_similar_to_all; group_itr++) {                    
                    double dtw_distance = calculateDTWDistance(
                        sub_trajectories[other.id],
                        sub_trajectories[group_id[group_itr]]
                    );

                    double cosine_similarity = calculateCosineSimilarity(
                        direction_vector[other.id],
                        direction_vector[group_id[group_itr]]
                    );

                    // make sure that the distance is not zero to avoid
                    // similarity checking when two entities
                    // doesn't appear in the current timeframe.
                    is_similar_to_all = dtw_distance != -1 && dtw_distance <= r &&
                        cosine_similarity >= cs;
                }

                if (is_similar_to_all) {
                    group_id.push_back(other.id);
                }
                */
            }

            for (size_t a = 0; a < group_ids.size(); a++) {
                for (size_t b = a + 1; b < group_ids.size(); b++) {
                    if (isSublist(group_ids[a], group_ids[b])) {
                        group_ids.erase(
                            group_ids.begin() + (group_ids[a].size() >= group_ids[b].size() ? a : b)
                        );
                    }
                }
            }

            for (std::vector<int> group: group_ids) {
                if (group.size() < m) {
                    continue;
                }

                bool is_new_group = true;

                for (std::vector<int> romb: rombongan_group) {
                    if (isSublist(romb, group)) {
                        is_new_group = false;
                        break;
                    }
                }

                if (is_new_group) {
                    rombongan_group.push_back(group);
                }
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

        std::cout << "Finished processing range [" << start << ", " << end << "]" << std::endl;
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

/**
 * Determine if a list is a sublist of another list
 * 
 * @param a the first list
 * @param b the second list
 * @return `true` if one of the supplied list if a sublist of another,
 * `false` otherwise
 */
bool isSublist(
    const std::vector<int>& a,
    const std::vector<int>& b
) {
    std::unordered_set<int> container;

    for (int member: a) {
        container.insert(member);
    }

    for (int member: b) {
        container.insert(member);
    }

    return container.size() == a.size() ||
        container.size() == b.size();
}
