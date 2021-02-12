#ifndef similarity
#define similarity

#include <vector>

double calculateDTWDistance(
    const std::vector<std::vector<double> >& a,
    const std::vector<std::vector<double> >& b
);
double calculateCosineSimilarity(
    const std::vector<double>& a,
    const std::vector<double>& b
);

#endif
