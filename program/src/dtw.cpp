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

    double distance = 0;

    for (int it = 0; it < (int)a.size(); it++) {
        distance += pow(a[it] - b[it], 2);
    }

    return sqrt(distance);
}

/**
 * Calculate dynamic time warping distance between two distinct
 * trajectories.
 */
double calculateDTWDistance(std::vector<std::vector<int> > &a, std::vector<std::vector<int> > &b) {
    // create a 2-dimensional array to store the DTW distances
    double dtw[a.size()][b.size()];

    // fill the DTW array with infinities
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b.size(); j++) {
            dtw[i][j] = std::numeric_limits<double>::max();
        }
    }

    // Pair the first point of `a` with the first point of `b`
    dtw[0][0] = 0;

    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b.size(); j++) {
            double cost = calculateCost(a[i], b[i]);
            double min = 

            dtw[i][j] = cost + std::min(
                dtw[i - 1][j],
                std::min(
                    dtw[i][j - 1],
                    dtw[i - 1][j - 1]
                )
            );
        }
    }

    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b.size(); j++) {
            printf("%.1lf ", dtw[i][j]);
        }

        printf("\n");
    }

    return dtw[a.size() - 1][b.size() - 1];
}