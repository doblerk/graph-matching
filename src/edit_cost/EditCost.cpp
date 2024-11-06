#include <array>
#include <string>
#include <vector>
#include <numeric>
#include <omp.h>
#include <boost/range/combine.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "graph_loader/GraphLoader.h"
#include "edit_cost/EditCost.h"


EditCost::EditCost(std::vector<int>& node_assignment, Graph& g1, Graph& g2)
    : node_assignment(node_assignment)
    , graph_source(g1)
    , graph_target(g2) {}

void EditCost::get_unassigned_nodes(int& num_nodes, std::vector<int>& unassigned_nodes) {
    int k = 0;
    for (int i = 0; i < num_nodes; i++) {
        if (std::find(node_assignment.begin(), node_assignment.end(), i) == node_assignment.end()) {
            unassigned_nodes[k] = i;
            k++;
        }
    }
}

void EditCost::calc_cost_node_edit(int& cost, 
                                   int& assignment_size, 
                                   const std::vector<int>& unassigned_nodes, 
                                   std::vector<std::string>& attrs_source, 
                                   std::vector<std::string>& attrs_target) {
    
    GraphLoader G;

    int j;

    // Node substitution cost
    for (int i = 0; i < assignment_size; ++i) {
        j = node_assignment[i];
        if (attrs_source[i] != attrs_target[j]) {
            // Add cost for node substitution (adjust this as needed)
            cost++;
        }
    }

    // cost node insertion
    cost += unassigned_nodes.size();

}

void EditCost::calc_cost_edge_edit(int& cost, int& num_nodes, std::vector<int>& unassigned_nodes) {

    GraphLoader G;

    // int num_nodes = G.get_num_nodes(graph_source); // redundant again

    // cost edge insertion, deletion, substitution
    for (int i = 0; i < num_nodes; i++) {
        
        int phi_i = node_assignment[i];

        for (int j = i + 1; j < num_nodes; j++) {

            int phi_j = node_assignment[j];

            if (G.has_edge(i, j, graph_source)) {

                if (G.has_edge(phi_i, phi_j, graph_target)) {
                    // add cost edge substitution
                } else {
                    // add cost edge deletion
                    cost++;
                }

            } else {

                if (G.has_edge(phi_i, phi_j, graph_target)) {
                    // add cost edge insertion
                    cost++;
                }
            }

        }

    }

    // cost edge insertion of unassigned nodes
    for (const int& i : unassigned_nodes) {
        cost += G.get_degree(i, graph_target);
    }

}