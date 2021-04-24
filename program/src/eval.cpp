#include "eval.h"
#include "rombongan.h"
#include <vector>
#include <algorithm>

/**
 * Find a group in a list of groups
 * 
 * @param source source list
 * @param value target value
 * 
 * @return `true` if value exists in source, `false`
 * otherwise
 */
bool find(
    const std::vector<std::vector<unsigned int> >& source,
    const std::vector<unsigned int>& value
) {
    return std::find(source.begin(), source.end(), value) != source.end();
}

/**
 * Calculate precision for the prediciton based on a ground truth
 * 
 * 
 * @param expected_result - ground truth
 * @param result - predicition
 * 
 * @return precision value.
 */
double calculate_precision(
    const std::vector<std::vector<unsigned int> >& expected_result,
    const std::vector<std::vector<unsigned int> >& result
) {
    double tp = 0;
    double fp = 0;

    for (size_t itr = 0; itr < result.size(); itr++) {
        find(expected_result, result[itr]) ?
            tp++ :
            fp++;
    }

    return tp / (tp + fp);
}

/**
 * Calculate recall for the prediciton based on a ground truth
 * 
 * @param expected_result - ground truth
 * @param result - predicition
 * 
 * @return recall value.
 */
double calculate_recall(
    const std::vector<std::vector<unsigned int> >& expected_result,
    const std::vector<std::vector<unsigned int> >& result
) {
    double tp = 0;
    double fn = 0;

    for (size_t itr = 0; itr < expected_result.size(); itr++) {
        find(result, expected_result[itr]) ?
            tp++ :
            fn++;
    }

    return tp / (tp + fn);
}

/**
 * Calculate f1 score for the prediciton based on a ground truth
 * 
 * @param expected_result - ground truth
 * @param result - predicition
 * 
 * @return evaluation result, including precision, recall, and F1 score
 */
Score calculate_score(
    const std::vector<std::vector<unsigned int> >& expected_result,
    const std::vector<Rombongan>& result
) {
    std::vector<std::vector<unsigned int> > result_ids;

    for (size_t itr = 0; itr < result.size(); itr++) {
        result_ids.push_back(result[itr].members);
    }

    double precision = calculate_precision(expected_result, result_ids);
    double recall = calculate_recall(expected_result, result_ids);
    double f1_score = 2 * (precision * recall) / (precision + recall);

    return {
        precision,
        recall,
        f1_score
    };
}