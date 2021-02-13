#include "rombongan.h"
#include "similarity.h"
#include "entity.h"
#include <vector>
#include <map>
#include <set>

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
    std::map<std::set<int>, std::pair<double, double> > paired_groups;
    std::vector<double> frames;
    unsigned int dimension;

    for (auto x: entities[0].trajectories) {
        frames.push_back(x.first);
        dimension = x.second.size();
    }

    for (unsigned int end = k; end < frames.size(); end++) {
        unsigned int start = end - k - 1;

        std::vector<std::set<int> > rombongan_group;

        for (Entity curr: entities) {
            std::set<Entity> group{ curr };

            for (Entity other: entities) {
                if (other.id != curr.id) {
                    bool is_similar_to_all = true;

                    for (Entity in_group: group) {
                        if (is_similar_to_all == false) {
                            break;
                        }

                        bool is_similar = true;

                        std::vector<std::vector<double> > sub_a, sub_b;
                        std::vector<double> vec_a, vec_b;

                        for (unsigned int i = start; i < end; i++) {
                            double ref = frames[i];

                            sub_a.push_back(in_group.trajectories[ref]);
                            sub_b.push_back(other.trajectories[ref]);
                        }

                        for (unsigned int i = 0; i < dimension; i++) {
                            vec_a.push_back(
                                in_group.trajectories[frames[end - 1]][i] - in_group.trajectories[frames[start]][i]
                            );
                            vec_b.push_back(
                                other.trajectories[frames[end - 1]][i] - other.trajectories[frames[start]][i]
                            );
                        }

                        is_similar = calculateDTWDistance(sub_a, sub_b) <= r &&
                            calculateCosineSimilarity(vec_a, vec_b);

                        is_similar_to_all = is_similar;
                    }

                    if (is_similar_to_all) {
                        group.insert(other);
                    }
                }
            }

            std::set<int> group_id;

            for (Entity member: group) {
                group_id.insert(member.id);
            }

            if (group.size() >= m) {
                rombongan_group.push_back(group_id);
            }
        }

        for (std::set<int> group: rombongan_group) {
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
