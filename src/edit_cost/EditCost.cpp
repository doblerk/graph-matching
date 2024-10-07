#include <array>
#include <string>
#include <vector>
#include <numeric>
#include <omp.h>
#include <boost/range/combine.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "graph_loader/GraphLoader.h"
#include "edit_cost/EditCost.h"


EditCost::EditCost(std::vector<int>& assignment, Graph g1, Graph g2)
    : node_assignment(assignment)
    , graph_source(g1)
    , graph_target(g2) {}

void EditCost::get_unassigned_nodes(const std::vector<int>& nodes, std::vector<int>& unassigned_nodes) {
    for (const int& i : nodes) {
        if (std::find(node_assignment.begin(), node_assignment.end(), i) == node_assignment.end()) {
            unassigned_nodes.push_back(i);
        }
    }
}

void EditCost::calc_cost_node_edit(int& cost, std::vector<int>& unassigned_nodes) {
    
    GraphLoader G;
    
    std::vector<std::string> attrs_source = G.get_node_attrs(graph_source);
    std::vector<std::string> attrs_target = G.get_node_attrs(graph_target);

    std::vector<int> idx(node_assignment.size());
    std::iota(idx.begin(), idx.end(), 0);

    // cost node substitution
    for (boost::tuple<int&, int&> tup : boost::combine(idx, node_assignment)) {
        int i, j;
        boost::tie(i, j) = tup;
        if (attrs_source[i] != attrs_target[j]) {
            // Do something... add unit cost... add euclidean cost...
            cost += 1;
        }
    }

    // cost node insertion
    // std::vector<int> nodes = G.get_nodes(graph_target);
    // std::vector<int> unassigned_nodes = get_unassigned_nodes(nodes);
    cost += unassigned_nodes.size();

}

void EditCost::calc_cost_edge_edit(int& cost, std::vector<int>& unassigned_nodes) {

    GraphLoader G;

    int num_nodes = G.get_num_nodes(graph_source);

    // cost edge insertion, deletion, substitution
    // #pragma omp parallel for num_threads(8) collapse(2)
    for (int i = 0; i < num_nodes; i++) {

        for (int j = i + 1; j < num_nodes; j++) {

            int phi_i = node_assignment[i];
            int phi_j = node_assignment[j];

            if (G.has_edge(i, j, graph_source) == 1) {

                if (G.has_edge(phi_i, phi_j, graph_target) == 1) {
                    // add cost edge substitution
                } else {
                    // add cost edge deletion
                    cost += 1;
                }

            } else {

                if (G.has_edge(phi_i, phi_j, graph_target) == 1) {
                    // add cost edge insertion
                    cost += 1;
                }
            }

        }

    }

    // cost edge insertion of unassigned nodes
    // std::vector<int> nodes = G.get_nodes(graph_target);
    // std::vector<int> unassigned_nodes = get_unassigned_nodes(nodes);
    // for each unassigned node, add cost for their incident edges
    for (const int& i : unassigned_nodes) {
        std::vector<int> e = G.get_adj_nodes(i, graph_target);
        cost += e.size();
    }

}