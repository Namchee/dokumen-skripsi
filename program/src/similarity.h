#ifndef similarity
#define similarity

#include <vector>

double calculate_dtw_distance(
    const std::vector<std::vector<double> >&,
    const std::vector<std::vector<double> >&
);
double calculate_cosine_similarity(
    const std::vector<double>&,
    const std::vector<double>&
);

#endif
