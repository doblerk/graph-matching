#ifndef EDITCOST_H
#define EDITCOST_H

#include <array>
#include <vector>
#include <string>
#include <numeric>
#include <omp.h>
#include <boost/range/combine.hpp>
#include <boost/graph/adjacency_list.hpp>
#include "../graph_loader/GraphLoader.h"


class EditCost {

    private:

        std::vector<int>& node_assignment;
        Graph& graph_source;
        Graph& graph_target;

    public:

        EditCost(std::vector<int>& node_assignment, Graph& g1, Graph& g2);

        void get_unassigned_nodes(int& num_nodes, std::vector<int>& unassigned_nodes);

        void calc_cost_node_edit(int& cost, int& assignment_size, const std::vector<int>& unassigned_nodes, std::vector<std::string>& attrs_source, std::vector<std::string>& attrs_target);

        void calc_cost_edge_edit(int& cost, int& num_nodes, std::vector<int>& unassigned_nodes);

};
#endif  // EDITCOST_H