#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <stdexcept>

/**
 * Calculate the euclidean distance between two points in
 * n-dimensional space.
 */
double calculateCost(std::vector<int> &a, std::vector<int> &b) {
    if (a.size() != b.size()) {
        throw std::length_error("Both trajectories must reside in the same dimensional space.");
    }

    double distance = 0.0f;

    for (unsigned int it = 0; it < a.size(); it++) {
        distance += pow(a[it] - b[it], 2);
    }

    return sqrt(distance);
}

/**
 * Calculate dynamic time warping distance between two distinct
 * trajectories.
 */
double calculateDTWDistance(std::vector<std::vector<int> > &a, std::vector<std::vector<int> > &b) {
    if (a.size() == 0 || b.size() == 0) {
        throw std::length_error("Both trajectories must not be empty.");
    }

    // create a 2-dimensional array to store the DTW distances
    int x_lim = a.size() + 1;
    int y_lim = b.size() + 1;
    double dtw[x_lim][y_lim];

    // initialize all illegal first pairings with infinity
    for (unsigned int i = 0; i < x_lim; i++) {
        dtw[i][0] = std::numeric_limits<double>::max();        
    }

    for (unsigned int i = 0; i < y_lim; i++) {
        dtw[0][i] = std::numeric_limits<double>::max();
    }

    // Pair the first point of `a` with the first point of `b`
    dtw[0][0] = 0;

    // Calculate DTW distance
    for (unsigned int i = 1; i < x_lim; i++) {
        for (unsigned int j = 1; j < y_lim; j++) {
            double cost = calculateCost(a[i - 1], b[j - 1]);

            double min = std::min(
                dtw[i - 1][j],
                std::min(
                    dtw[i][j - 1],
                    dtw[i - 1][j - 1]
                )
            );

            dtw[i][j] = cost + min;
        }
    }

    return dtw[a.size()][b.size()];
}