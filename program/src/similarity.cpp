#include <vector>
#include <limits>
#include <cmath>
#include <algorithm>
#include <stdexcept>

/**
 * Calculate the euclidean distance between two points in
 * n-dimensional space.
 * 
 * @param a the first point
 * @param b the second point
 * @return Euclidean distance between two points `a` and `b`
 */
double calculate_euclidean_distance(
    const std::vector<double> &a,
    const std::vector<double> &b
) {
    if (a.size() != b.size()) {
        throw std::invalid_argument(
            "Both trajectories must reside in the same dimensional space."
        );
    }

    double distance = 0.0;

    for (size_t it = 0; it < a.size(); it++) {
        // return immediately when one of the position is not recorded
        if (a[it] == -1 || b[it] == -1) {
            return -1;
        }

        distance += pow(a[it] - b[it], 2);
    }

    return sqrt(distance);
}

/**
 * Calculate dynamic time warping distance between two distinct
 * trajectories.
 * 
 * @param a the first trajectory
 * @param b the second trajectory
 * @return Dynamic time warping distance between two trajectories
 * `a` and `b`
 */
double calculate_dtw_distance(
    const std::vector<std::vector<double> >& a,
    const std::vector<std::vector<double> >& b
) {
    if (a.size() == 0 || b.size() == 0) {
        throw std::invalid_argument("Both trajectories must not be empty.");
    }

    // create a 2-dimensional array to store the DTW distances
    const size_t x_lim = a.size() + 1;
    const size_t y_lim = b.size() + 1;
    double dtw[x_lim][y_lim];

    // initialize all illegal first pairings with infinity
    for (size_t i = 0; i < x_lim; i++) {
        dtw[i][0] = std::numeric_limits<double>::max();        
    }

    for (size_t i = 0; i < y_lim; i++) {
        dtw[0][i] = std::numeric_limits<double>::max();
    }

    // Pair the first point of `a` with the first point of `b`
    dtw[0][0] = 0;

    // Calculate DTW distance
    for (size_t i = 1; i < x_lim; i++) {
        for (size_t j = 1; j < y_lim; j++) {
            double cost = calculate_euclidean_distance(
                a[i - 1],
                b[j - 1]
            );

            // return immediately when trajectory isn't recorded
            if (cost == -1) {
                return -1;
            }

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

/**
 * Calculate cosine similarity between two n-dimensional vector.
 * 
 * @param a - the first vector
 * @param b - the second vector
 * @return 
 */
double calculate_cosine_similarity(
    const std::vector<double>& a,
    const std::vector<double>& b
) {
    // sanity check
    if (a.size() != b.size()) {
        throw std::invalid_argument(
            "Both vector must reside in the same dimensional space."
        );
    }

    double len_a = 0.0;
    double len_b = 0.0;
    double dot_product = 0.0;

    for (size_t itr = 0; itr < a.size(); itr++) {
        // return immediately when one of the position is not recorded
        if (a[itr] == -1 || b[itr] == -1) {
            return -1;
        }

        dot_product += a[itr] * b[itr];

        len_a += pow(a[itr], 2);
        len_b += pow(b[itr], 2);
    }

    len_a = sqrt(len_a);
    len_b = sqrt(len_b);

    return dot_product / (len_a * len_b);
}