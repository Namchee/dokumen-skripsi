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

    // example: minimum interval is 3, then the time window starts from [0, 2]
    for (unsigned int end = k - 1; end < entities.size(); end++) {
        unsigned int start = end - k;

        std::vector<std::unordered_set<int> > rombongan;

        for (Entity curr: entities) {
            std::set<Entity> group;
            group.insert(curr);

            for (Entity other: entities) {
                // only calculate when other is not the same entity as
                // curr.
                if (curr.id != other.id) {
                    bool isSimilar = true;

                    std::vector<std::vector<double> > sub_curr = std::vector<std::vector<double> >(
                        curr.trajectories.begin() + start,
                        curr.trajectories.begin() + end
                    );
                    std::vector<std::vector<double> > sub_other = std::vector<std::vector<double> >(
                        other.trajectories.begin() + start,
                        other.trajectories.begin() + end
                    );
                }
            }
        }
    }

    return result;
}