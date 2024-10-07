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

    NodeAssignment::NodeAssignment(std::vector<std::vector<float>> source_embedding, std::vector<std::vector<float>> target_embedding)
        : source(source_embedding)
        , target(target_embedding) {}

    float NodeAssignment::euclidean_distance(const std::vector<float>& a, const std::vector<float>& b) {
        float sum = 0.0;
        #pragma omp parallel for reduction(+:sum)
        for (int i = 0; i < a.size(); i++) {
            float diff = a[i] - b[i];
            sum += std::pow(diff, 2);
        }
        return std::sqrt(sum);
    }

    std::vector<std::vector<float>> NodeAssignment::calc_cost_matrix() {

        int rows1 = source.size();
        int rows2 = target.size();

        std::vector<std::vector<float>> distances(rows1, std::vector<float>(rows2));

        // #pragma omp parallel for num_threads(4) collapse(2)
        for (int i = 0; i < rows1; i++) {
            for (int j = 0; j < rows2; j++) {
                distances[i][j] = euclidean_distance(source[i], target[j]);
            }
        }
        return distances;
    }

    void NodeAssignment::injective_assignment(std::vector<int>& node_assignment, std::vector<std::vector<float>> cost_matrix, int max_dim) {
        SimpleLinearSumAssignment assignment;

        std::vector<std::vector<float>> extended_cost_matrix(max_dim, std::vector<float>(max_dim, 100));

        int num_dummy_workers = extended_cost_matrix.size() - cost_matrix.size();   // number of dummy nodes added

        #pragma omp parallel for num_threads(4) collapse(2)
        for (int i = 0; i < cost_matrix.size(); i++) {
            for (int j = 0; j < cost_matrix[0].size(); j++) {
                extended_cost_matrix[i][j] = cost_matrix[i][j];
            }
        }

        #pragma omp parallel for num_threads(4) collapse(2)
        for (int worker = 0; worker < max_dim; worker++) {
            for (int task = 0; task < max_dim; task++) {
                assignment.AddArcWithCost(worker, task, extended_cost_matrix[worker][task]);
            }
        }

        SimpleLinearSumAssignment::Status status = assignment.Solve();

        for (int worker = 0; worker < cost_matrix.size(); worker++) {
            node_assignment[worker] = assignment.RightMate(worker);
        }

    }

    void NodeAssignment::bijective_assignment(std::vector<int>& node_assignment, std::vector<std::vector<float>> cost_matrix) {
        SimpleLinearSumAssignment assignment;

        #pragma omp parallel for num_threads(4) collapse(2)
        for (int worker = 0; worker < cost_matrix.size(); worker++) {
            for (int task = 0; task < cost_matrix[0].size(); task++) {
                assignment.AddArcWithCost(worker, task, cost_matrix[worker][task]);
            }
        }

        SimpleLinearSumAssignment::Status status = assignment.Solve();

        for (int worker = 0; worker < cost_matrix.size(); worker++) {
            node_assignment[worker] = assignment.RightMate(worker);
        }
    }

    std::vector<int> NodeAssignment::calc_node_assignment() {

        const std::vector<std::vector<float>> cost_matrix = calc_cost_matrix();

        int num_workers = cost_matrix.size();   // number of nodes in the source graph
        int num_tasks = cost_matrix[0].size();  // number of nodes in the target graph
        int max_dim = std::max(num_workers, num_tasks);

        std::vector<int> node_assignment(num_workers);

        if (num_workers < num_tasks) {

            injective_assignment(node_assignment, cost_matrix, max_dim);

        } else {

            bijective_assignment(node_assignment, cost_matrix);
        }

        return node_assignment;

    }

}