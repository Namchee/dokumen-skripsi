#include "similarity.h"
#include "entity.h"
#include <vector>
#include <set>
#include <unordered_set>

/**
 * Identify rombongan from a set of moving entities.
 * 
 * @param entities - list of moving entities in two-dimensional space
 */
std::vector<std::vector<std::unordered_set<int> > > identifyRombongan(
    const std::vector<Entity>& entities,
    int m,
    int k,
    double r,
    double cs
) {
    std::vector<std::vector<std::unordered_set<int> > > result;
    int dimension = entities[0].trajectories[0].size();

    // example: minimum interval is 3, then the time window starts from [0, 2]
    for (unsigned int end = k - 1; end < entities.size(); end++) {
        unsigned int start = end - k;

        std::vector<std::unordered_set<int> > rombongan;

        for (Entity curr: entities) {
            std::unordered_set<Entity, EntityHasher> group{ curr };

            for (Entity other: entities) {
                if (other.id != curr.id) {
                    bool is_similar_to_all = true;

                    for (Entity in_group: group) {
                        if (is_similar_to_all == false) {
                            break;
                        }

                        bool is_similar = true;

                        std::vector<std::vector<double> > sub_a = std::vector<std::vector<double> >(
                            in_group.trajectories.begin() + start,
                            in_group.trajectories.begin() + end
                        );

                        std::vector<std::vector<double> > sub_b = std::vector<std::vector<double> >(
                            other.trajectories.begin() + start,
                            other.trajectories.begin() + end  
                        );

                        std::vector<double> vec_a, vec_b;
                        
                        for (unsigned int i = 0; i < dimension; i++) {
                            vec_a.push_back(
                                in_group.trajectories[end][i] - in_group.trajectories[start][i]
                            );
                            vec_b.push_back(
                                other.trajectories[end][i] - other.trajectories[start][i]
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

            std::unordered_set<int> group_id;

            for (Entity member: group) {
                group_id.insert(member.id);
            }

            if (group.size() >= m) {
                rombongan.push_back(group_id);
            }
        }

        result.push_back(rombongan);
    }

    return result;
}