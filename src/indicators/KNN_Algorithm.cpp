// #include "KNN_Algorithm.hpp"
// #include <cmath>
// #include <algorithm>

// int KNN::calculate( std::vector<std::vector<double>>& data,  std::vector<double>& target, int k) {
//     std::vector<std::pair<double, int>> distances;

//     for (std::size_t i = 0; i < data.size(); ++i) {
//         double distance = 0.0;
//         for (size_t j = 0; j < data[i].size(); ++j) {
//             distance += std::pow(data[i][j] - target[j], 2);
//         }
//         distances.emplace_back(std::sqrt(distance), i);
//     }

//     std::sort(distances.begin(), distances.end());

//     std::vector<int> votes(2, 0); // Assuming binary classification
//     for (size_t i = 0; i < k; ++i) {
//         votes[target[distances[i].second]]++;
//     }

//     return (votes[0] > votes[1]) ? 0 : 1;
// }
