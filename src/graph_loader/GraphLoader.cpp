#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/graph/graphml.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>
#include "graph_loader/GraphLoader.h"


GraphLoader::GraphLoader() {}

void GraphLoader::read_graph(const std::string &filename, Graph &g) {
    std::ifstream InFile;
    InFile.open(filename, std::ifstream::in);
    boost::dynamic_properties dp(boost::ignore_other_properties);
    dp.property("attr", boost::get(&VertexProperties::attr, g));
    boost::read_graphml(InFile, g, dp);
    InFile.close();
}

void GraphLoader::print_graph(Graph &g) {
    auto vertices = boost::vertices(g);
    std::cout << "Vertices:" << std::endl;
    for (auto it = vertices.first; it != vertices.second; ++it) {
        std::cout << *it << " : " << g[*it].attr  << std::endl;
    }

    auto edges = boost::edges(g);
    std::cout << "Edges:" << std::endl;
    for (auto it = edges.first; it != edges.second; ++it) {
        std::cout << boost::source(*it, g) << " -> " << boost::target(*it, g) << std::endl;
    }
}

std::vector<std::string> GraphLoader::get_node_attrs(Graph &g) {
    std::vector<std::string> node_attributes;
    auto vertices = boost::vertices(g);
    for (auto it = vertices.first; it != vertices.second; ++it) {
        node_attributes.push_back(g[*it].attr);
    }
    return node_attributes;
}

std::vector<int> GraphLoader::get_nodes(Graph &g) {
    std::vector<int> nodes;
    std::pair<boost::graph_traits<Graph>::vertex_iterator, boost::graph_traits<Graph>::vertex_iterator> vertices = boost::vertices(g);
    for (boost::graph_traits<Graph>::vertex_iterator it = vertices.first; it != vertices.second; ++it) {
        nodes.push_back(*it);
    }
    return nodes;
}

int GraphLoader::get_num_nodes(Graph &g) {
    int num_nodes = boost::num_vertices(g);
    return num_nodes; 
}

std::vector<int> GraphLoader::get_adj_nodes(int u, Graph &g) {
    typename GraphTraits::out_edge_iterator ei, ei_end;
    std::vector<int> adjacent_nodes;
    for (boost::tie(ei, ei_end) = out_edges(u, g); ei != ei_end; ++ei) {
        int target = boost::target( *ei, g );
        adjacent_nodes.push_back(target);
    }
    return adjacent_nodes;
}

int GraphLoader::get_degree(int u, Graph &g) {
    int out_degree = boost::out_degree(u, g);
    return out_degree;
}

int GraphLoader::has_edge(int u, int v, Graph &g) {
    int e = boost::edge(u, v, g).second;
    return e;
}