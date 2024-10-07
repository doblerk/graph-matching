#ifndef GRAPHLOADER_H
#define GRAPHLOADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/graph/graphml.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/property_map/dynamic_property_map.hpp>

struct VertexProperties {
    std::string attr;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor Vertex;
typedef boost::graph_traits<Graph> GraphTraits;

class GraphLoader {
        
    public: 

        GraphLoader();

        void read_graph(const std::string &filename, Graph &g);

        void print_graph(Graph &g);

        std::vector<std::string> get_node_attrs(Graph &g);

        std::vector<int> get_nodes(Graph &g);

        int get_num_nodes(Graph &g);

        std::vector<int> get_adj_nodes(int u, Graph &g);

        int has_edge(int u, int v, Graph &g);

};
#endif  // GRAPHLOADER_H