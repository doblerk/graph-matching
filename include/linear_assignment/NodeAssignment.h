#ifndef NODEASSIGNMENT_H
#define NODEASSIGNMENT_H

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


namespace operations_research {

    class NodeAssignment {

        private:
            
            std::vector<std::vector<float>>& source;
            std::vector<std::vector<float>>& target;
            std::vector<std::vector<float>> cost_matrix;

        public:

            NodeAssignment(std::vector<std::vector<float>>& source_embedding, std::vector<std::vector<float>>& target_embedding);

            const std::vector<std::vector<float>>& getSource() const { return source; }
            
            const std::vector<std::vector<float>>& getTarget() const { return target; }
            
            const std::vector<std::vector<float>>& getCostMatrix() const { return cost_matrix; }

            float euclidean_distance(const std::vector<float>& a, const std::vector<float>& b);

            void calc_cost_matrix();

            void linear_assignment(std::vector<int>& node_assignment);

            void greedy_assignment(std::vector<int>& node_assignment);

            // void calc_node_assignment(std::vector<int>& node_assignment);

    };

}
#endif  // NODEASSIGNMENT_H