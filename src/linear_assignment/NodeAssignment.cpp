#include <cstdint>
#include <numeric>
#include <string>
#include <vector>
#include <chrono>
#include <omp.h>
#include "cnpy.h"
#include "ortools/graph/assignment.h"
#include "linear_assignment/NodeAssignment.h"


namespace operations_research {

    NodeAssignment::NodeAssignment(std::vector<std::vector<float>>& source_embedding, std::vector<std::vector<float>>& target_embedding)
        : source(source_embedding)
        , target(target_embedding)
        , cost_matrix(target_embedding.size(), std::vector<float>(target_embedding.size(), 1.0f)) {}

    float NodeAssignment::euclidean_distance(const std::vector<float>& a, const std::vector<float>& b) {
        float sum = 0.0;
        for (int k = 0; k < source.size(); k++) {
            float diff = a[k] - b[k];
            sum += diff * diff;
        }
        return sum;
    }

    void NodeAssignment::calc_cost_matrix() {

        #pragma omp parallel for collapse(2) num_threads(8)
        for (int i = 0; i < source.size(); i++) {
            for (int j = 0; j < target.size(); j++) {
                cost_matrix[i][j] = std::sqrt(euclidean_distance(source[i], target[j]));
            }
        }
    }

    void NodeAssignment::linear_assignment(std::vector<int>& node_assignment) {

        SimpleLinearSumAssignment assignment;

        for (int worker = 0; worker < cost_matrix.size(); worker++) {
            for (int task = 0; task < cost_matrix[0].size(); task++) {
                assignment.AddArcWithCost(worker, task, cost_matrix[worker][task]);
            }
        }

        SimpleLinearSumAssignment::Status status = assignment.Solve();

        for (int worker = 0; worker < node_assignment.size(); worker++) {
            node_assignment[worker] = assignment.RightMate(worker);
        }

    }

    void NodeAssignment::calc_node_assignment(std::vector<int>& node_assignment) {

        calc_cost_matrix();

        linear_assignment(node_assignment);

    }

}