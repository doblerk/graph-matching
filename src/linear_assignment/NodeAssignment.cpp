#include <cstdint>
#include <numeric>
#include <set>
#include <map>
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
        , target(target_embedding) {}
        // , cost_matrix(target_embedding.size(), std::vector<float>(target_embedding.size(), 1.0f)) {}

    float NodeAssignment::euclidean_distance(const std::vector<float>& a, const std::vector<float>& b) {
        float sum = 0.0;
        for (int k = 0; k < source.size(); k++) {
            float diff = a[k] - b[k];
            sum += diff * diff;
        }
        return sum;
    }

    void NodeAssignment::calc_cost_matrix(std::vector<float>& cost_matrix) {

        #pragma omp parallel for collapse(2) num_threads(8)
        for (int i = 0; i < source.size(); i++) {
            for (int j = 0; j < target.size(); j++) {
                // cost_matrix[i][j] = std::sqrt(euclidean_distance(source[i], target[j]));
                cost_matrix[i * target.size() + j] = std::sqrt(euclidean_distance(source[i], target[j]));
                
            }
        }
    }

    void NodeAssignment::linear_assignment(std::vector<int>& node_assignment, std::vector<float>& cost_matrix) {

        SimpleLinearSumAssignment assignment;

        for (int worker = 0; worker < target.size(); worker++) {
            for (int task = 0; task < target.size(); task++) {
                assignment.AddArcWithCost(worker, task, cost_matrix[worker * target.size() + task]);
            }
        }

        SimpleLinearSumAssignment::Status status = assignment.Solve();

        for (int worker = 0; worker < node_assignment.size(); worker++) {
            node_assignment[worker] = assignment.RightMate(worker);
        }

    }

    void NodeAssignment::greedy_assignment(std::vector<int>& node_assignment, std::vector<float>& cost_matrix) {
        
        std::vector<std::set<std::pair<int, int>>> sorted_rows(source.size());
        std::vector<std::set<std::pair<int, int>>> sorted_cols(target.size());

        std::vector<bool> rowNotDeleted(source.size(), true);
        std::vector<bool> colNotDeleted(target.size(), true);

        for (int i = 0; i < source.size(); i++) {

            for (int j = 0; j < target.size(); j++) {
                float cost = cost_matrix[i * target.size() + j];
                sorted_rows[i].insert(std::make_pair(cost, j));
                sorted_cols[j].insert(std::make_pair(cost, i));

            }

        }

        for (int k = 0; k < source.size(); k++) {

            int min_cost = 100, min_row = -1, min_col = -1;

            for (int i = 0; i < source.size(); i++) {
                if (rowNotDeleted[i] && !sorted_rows[i].empty()) {
                    auto [cost, col] = *sorted_rows[i].begin();
                    if (cost < min_cost) {
                    min_cost = cost;
                    min_row = i;
                    min_col = col;
                    }
                }
            }

            for (int i = 0; i < target.size(); i++) {
                if (colNotDeleted[i] && !sorted_cols[i].empty()) {
                    auto [cost, row] = *sorted_cols[i].begin();
                    if (cost < min_cost) {
                    min_cost = cost;
                    min_row = row;
                    min_col = i;
                    }
                }
            }

            node_assignment[min_row] = min_col;

            rowNotDeleted[min_row] = false;
            colNotDeleted[min_col] = false;

            for (int i = 0; i < source.size(); ++i) {
                if (rowNotDeleted[i]) {
                    sorted_rows[i].erase({cost_matrix[i * target.size() + min_col], min_col});
                }
            }

            for (int j = 0; j < target.size(); ++j) {
                if (colNotDeleted[j]) {
                    sorted_cols[j].erase({cost_matrix[min_row * target.size() + j], min_row});
                }
            }

        }

    }

    void NodeAssignment::greedy_assignment_fast(std::vector<int>& node_assignment, std::vector<float>& cost_matrix) {

        std::vector<bool> rowNotDeleted(source.size(), true);
        std::vector<bool> colNotDeleted(target.size(), true);
        
        float tmp_cost, min_cost;
        int min_row, min_col;

        for (int k = 0; k < source.size(); ++k) {
            min_cost = std::numeric_limits<float>::max();
            min_row = -1, min_col = -1;

            for (int i = 0; i < source.size(); ++i) {
                if (rowNotDeleted[i]) {
                    for (int j = 0; j < target.size(); ++j) {
                        if (colNotDeleted[j]) {
                            tmp_cost = cost_matrix[i * target.size() + j];
                            if (tmp_cost < min_cost) {
                                min_cost = tmp_cost;
                                min_row = i;
                                min_col = j;
                            }
                        }
                    }
                }
            }

            node_assignment[min_row] = min_col;

            rowNotDeleted[min_row] = false;
            colNotDeleted[min_col] = false;
        }

    }

    void NodeAssignment::minimum_cost_flow(std::vector<int>& node_assignment, std::vector<float>& cost_matrix) {
        // TODO
    }


}