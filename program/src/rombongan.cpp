#include "rombongan.h"
#include "similarity.h"
#include "entity.h"
#include "io.h"
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <iostream>

typedef std::unordered_map<unsigned int, std::vector<std::vector<double> > > trajectory_map;
typedef std::unordered_map<unsigned int, std::vector<double> > direction_map;
typedef std::map<std::vector<unsigned int>, std::vector<std::pair<double, double> > > rombongan_lifespan;

class Metadata {
public:
    std::vector<double> frames;
    size_t dimension;
};

class FrameInformation {
public:
    std::vector<double> frames;
    size_t start, end;
};

/**
 * Determine is a list is a imperfect sublist of another.
 *
 * @param a - first list
 * @param b - second list
 * @return `true` if a list is a imperfect sublist of another,
 * `false` otherwise
 */
bool is_sublist(
    const std::vector<unsigned int>& a,
    const std::vector<unsigned int>& b
) {
    std::set<unsigned int> temp_container;
    temp_container.insert(a.begin(), a.end());
    temp_container.insert(b.begin(), b.end());

    return a.size() != b.size() &&
        (
            temp_container.size() == a.size() ||
            temp_container.size() == b.size()
        );
}

std::vector<Rombongan> clean_result(
    std::vector<Rombongan>& raw_result,
    double fps
) {
    std::sort(raw_result.begin(), raw_result.end());

    for (size_t curr_itr = 0; curr_itr < raw_result.size(); curr_itr++) {
        for (size_t other_itr = curr_itr + 1; other_itr < raw_result.size(); other_itr++) {
            if (raw_result[other_itr].duration.size() == 0) {
                continue;
            }

            if (is_sublist(raw_result[curr_itr].members, raw_result[other_itr].members)) {
                std::vector<std::pair<double, double> > parent = raw_result[curr_itr].duration;

                for (size_t parent_itr = 0; parent_itr < parent.size(); parent_itr++) {
                    std::pair<double, double> par_dur = parent[parent_itr];

                    for (size_t child_itr = 0; child_itr < raw_result[other_itr].duration.size(); child_itr++) {
                        std::pair<double, double> chi_dur = raw_result[other_itr].duration[child_itr];

                        if (
                            (par_dur == chi_dur) ||
                            (abs(par_dur.first - chi_dur.first) <= fps) ||
                            (abs(par_dur.second - chi_dur.second) <= fps)
                        ) {
                            raw_result[other_itr].duration.erase(
                                raw_result[other_itr].duration.begin() + child_itr
                            );
                        }
                    }
                }
            }
        }
    }

    std::vector<Rombongan> clean_result;

    for (auto member: raw_result) {
        if (member.duration.size() > 0) {
            clean_result.push_back(member);
        }
    }

    sort(
        clean_result.begin(),
        clean_result.end(),
        [](const Rombongan& a, const Rombongan& b) -> bool {
            return a.duration[0].first < b.duration[0].first;
        }
    );

    return clean_result;
}

/**
 * Get entities metadata from input.
 * 
 * @param entities - input entities
 */
Metadata get_metadata(
    const std::vector<Entity>& entities
) {
    std::vector<double> frames;

    for (auto const& trajectory: entities[0].trajectories) {
        frames.push_back(trajectory.first);
    }

    size_t dimension = (*entities[0].trajectories.begin()).second.size();

    return Metadata{
        frames,
        dimension
    };
}

/**
 * Get sub trajectories from all entities for a time interval
 * 
 * @param entities - input entities
 * @param frame_info list of frames and desired duration
 */
trajectory_map get_sub_trajectories(
    const std::vector<Entity>& entities,
    const FrameInformation& frame_info
) {
    auto [frames, start, end] = frame_info;
    trajectory_map sub_trajectories;

    for (size_t itr = 0; itr < entities.size(); itr++) {
        Entity curr = entities[itr];

        for (size_t frame = start; frame < end; frame++) {
            double current_frame = frames[frame];

            sub_trajectories[curr.id].push_back(
                curr.trajectories[current_frame]
            );
        }
    }

    return sub_trajectories;
}

/**
 * Get directional vectors for all entities in a time interval
 * 
 * @param entities list of entities
 * @param frame_info list of frames and desired duration
 * @param dimension trajectory dimension
 */
direction_map get_directional_vectors(
    const std::vector<Entity>& entities,
    const FrameInformation& frame_info,
    unsigned short dimension
) {
    auto [frames, start, end] = frame_info;

    direction_map directional_vectors;

    for (size_t itr = 0; itr < entities.size(); itr++) {
        Entity curr = entities[itr];
        std::vector<double> end_pos = curr.trajectories[frames[end - 1]];
        std::vector<double> start_pos = curr.trajectories[frames[start]];

        for (size_t curr_dimension = 0; curr_dimension < dimension; curr_dimension++) {
            directional_vectors[curr.id].push_back(
                end_pos[curr_dimension] - start_pos[curr_dimension]
            );
        }
    }

    return directional_vectors;
}

void extend_current_rombongan(
    std::vector<std::vector<unsigned int> >& groups,
    const Entity& other,
    trajectory_map& sub_trajectories,
    direction_map& direction_vector,
    const Parameters& params
) {
    double r = params.range;
    double cs = params.cosine_similarity;

    for (size_t groups_itr = 0; groups_itr < groups.size(); groups_itr++) {
        bool is_similar_to_all_members = true;

        for (int member_id: groups[groups_itr]) {
            double dtw_distance = calculate_dtw_distance(
                sub_trajectories[other.id],
                sub_trajectories[member_id]
            );

            double cosine_similarity = calculate_cosine_similarity(
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
            std::vector new_group = std::vector<unsigned int>(
                groups[groups_itr].begin(),
                groups[groups_itr].end()
            );

            new_group.push_back(other.id);
            groups.push_back(new_group);
        }
    }
}

void extend_rombongan_duration(
    rombongan_lifespan& groups,
    std::vector<std::vector<unsigned int> >& current_groups,
    const FrameInformation& frame_info
) {
    auto [frames, start, end] = frame_info;

    for (std::vector<unsigned int> group: current_groups) {
        std::vector<std::pair<double, double> > time_list = groups[group];

        if (
            time_list.size() == 0 ||
            start == 0 ||
            frames[end - 1] != time_list[time_list.size() - 1].second
        ) {
            groups[group].push_back({ frames[start], frames[end] });
        } else {
            groups[group][time_list.size() - 1] = { 
                groups[group][time_list.size() - 1].first,
                frames[end]
            };
        }
    }
}

/**
 * Identify rombongan from a set of moving entities.
 * 
 * @param entities - list of moving entities in two-dimensional space
 */
std::vector<Rombongan> identify_rombongan(
    const std::vector<Entity>& entities,
    const Parameters& params
) {
    int m = params.entity_count;
    int k = params.time_interval;
    double r = params.range;
    double cs = params.cosine_similarity;

    rombongan_lifespan rombongan_list;
    auto [frames, dimension] = get_metadata(entities);

    for (size_t end = k; end < frames.size(); end++) {
        unsigned int start = end - k;

        std::vector<std::vector<unsigned int> > current_rombongan;

        FrameInformation frame_info = FrameInformation{
            frames,
            start,
            end
        };

        trajectory_map sub_trajectories = get_sub_trajectories(
            entities,
            frame_info
        );
        direction_map direction_vector = get_directional_vectors(
            entities,
            frame_info,
            dimension
        );

        for (size_t curr_itr = 0; curr_itr < entities.size(); curr_itr++) {
            Entity curr = entities[curr_itr];
            std::vector<std::vector<unsigned int> > group_ids;

            for (size_t other_itr = curr_itr + 1; other_itr < entities.size(); other_itr++) {
                Entity other = entities[other_itr];

                extend_current_rombongan(
                    group_ids,
                    other,
                    sub_trajectories,
                    direction_vector,
                    params
                );

                // can entity `curr` create a subgroup with `other`?
                double dtw_distance = calculate_dtw_distance(
                    sub_trajectories[other.id],
                    sub_trajectories[curr.id]
                );

                double cosine_similarity = calculate_cosine_similarity(
                    direction_vector[other.id],
                    direction_vector[curr.id]
                );

                if (dtw_distance != -1 && dtw_distance <= r && cosine_similarity >= cs) {
                    group_ids.push_back({ curr.id, other.id });
                }
            }

            for (size_t itr_group = 0; itr_group < group_ids.size(); itr_group++) {
                if (group_ids[itr_group].size() >= m) {
                    current_rombongan.push_back(group_ids[itr_group]);
                }
            }
        }

        extend_rombongan_duration(
            rombongan_list,
            current_rombongan,
            frame_info
        );

        std::cout << "Finished processing range ";
        std::cout << "[" << start << ", " << end << "]" << std::endl;
    }

    std::vector<Rombongan> raw_result;

    for (auto const& [group, duration]: rombongan_list) {
        raw_result.push_back({
            group,
            duration
        });
    }

    return clean_result(raw_result, params.fps);
}
