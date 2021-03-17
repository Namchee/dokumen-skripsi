#include "rombongan.h"
#include "similarity.h"
#include "entity.h"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <iostream>


/**
 * Determine if a list is a sublist of another list
 * 
 * @param a the first list
 * @param b the second list
 * @return `true` if one of the supplied list if a sublist of another,
 * `false` otherwise
 */
bool is_sublist(
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
        if (end >= 25) {
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
                        is_similar_to_all_members = dtw_distance != -1 &&
                            dtw_distance <= r &&
                            cosine_similarity >= cs;

                        if (!is_similar_to_all_members) {
                            break;
                        }
                    }

                    if (is_similar_to_all_members) {
                        group_ids[groups_itr].push_back(other.id);
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

            /*
            bool sublist_mark[group_ids.size()] = { false };

            for (size_t a = 0; a < group_ids.size(); a++) {
                if (sublist_mark[a]) {
                    continue;
                }

                for (size_t b = a + 1; b < group_ids.size(); b++) {
                    if (is_sublist(group_ids[a], group_ids[b])) {
                        sublist_mark[b] = true;
                    }
                }
            }

            for (size_t itr_group = 0; itr_group < group_ids.size(); itr_group++) {
                std::vector<int> group = group_ids[itr_group];

                if (group.size() < m) {
                    continue;
                }

                bool is_new_group = true;

                for (std::vector<int> rombongan_member: rombongan_group) {
                    if (is_sublist(rombongan_member, group)) {
                        is_new_group = false;
                        break;
                    }
                }

                if (is_new_group) {
                    rombongan_group.push_back(group);
                } else {
                    rombongan_group.push_back(group);
                }
            }
            */
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
