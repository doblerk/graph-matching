#include <cstdint>
#include <numeric>
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "ortools/graph/assignment.h"
#include "linear_assignment/NodeAssignment.h"


using namespace operations_research;


class NodeAssignmentTest : public ::testing::Test {
    
    protected:
        
        std::vector<std::vector<float>> source_embedding = {
            {1.0, 2.0}, {3.0, 4.0}, {5.0, 6.0}
        };
        
        std::vector<std::vector<float>> target_embedding = {
            {1.1, 2.1}, {3.1, 4.1}, {5.1, 6.1}
        };

        NodeAssignment node_assignment = NodeAssignment(source_embedding, target_embedding);

};

// Test Constructor
TEST_F(NodeAssignmentTest, ConstructorTest) {
    EXPECT_EQ(node_assignment.getSource().size(), source_embedding.size());
    EXPECT_EQ(node_assignment.getTarget().size(), target_embedding.size());
}

// Test Cost Matrix Calculation
TEST_F(NodeAssignmentTest, CalcCostMatrixTest) {
    std::vector<float> cost_matrix(target_embedding.size() * target_embedding.size());
    node_assignment.calc_cost_matrix(cost_matrix);

    for (int i = 0; i < source_embedding.size(); i++) {
        for (int j = 0; j < target_embedding.size(); j++) {
            float expected_cost = std::sqrt(node_assignment.euclidean_distance(
                source_embedding[i], target_embedding[j]));
            EXPECT_FLOAT_EQ(cost_matrix[i * target_embedding.size() + j], expected_cost);
        }
    }
}

// Test Linear Assignment
TEST_F(NodeAssignmentTest, LinearAssignmentTest) {
    std::vector<float> cost_matrix(target_embedding.size() * target_embedding.size());
    node_assignment.calc_cost_matrix(cost_matrix);

    std::vector<int> node_assignment_result(3);
    node_assignment.linear_assignment(node_assignment_result, cost_matrix);

    // Expected result: minimal cost assignment indices
    EXPECT_EQ(node_assignment_result[0], 0);  // First worker assigned to first task
    EXPECT_EQ(node_assignment_result[1], 1);  // Second worker assigned to second task
    EXPECT_EQ(node_assignment_result[2], 2);  // Third worker assigned to third task
}