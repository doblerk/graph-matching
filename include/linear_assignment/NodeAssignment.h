#ifndef NODEASSIGNMENT_H
#define NODEASSIGNMENT_H

#include <cstdint>
#include <numeric>
#include <string>
#include <vector>
#include <chrono>
#include <omp.h>
#include "cnpy.h"
#include "ortools/graph/assignment.h"


namespace operations_research {

    class NodeAssignment {

        private:

            std::vector<std::vector<float>> source;
            std::vector<std::vector<float>> target;

        public:

            NodeAssignment(std::vector<std::vector<float>> source_embedding, std::vector<std::vector<float>> target_embedding);

            float euclidean_distance(const std::vector<float>& a, const std::vector<float>& b);

            std::vector<std::vector<float>> calc_cost_matrix();

            void injective_assignment(std::vector<int>& node_assignment, std::vector<std::vector<float>> cost_matrix, int max_dim);

            void bijective_assignment(std::vector<int>& node_assignment, std::vector<std::vector<float>> cost_matrix);

            std::vector<int> calc_node_assignment();

    };

}
#endif  // NODEASSIGNMENT_H