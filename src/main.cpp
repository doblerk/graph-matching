// This is the main script that handles everything
#include <string>
#include <regex>
#include <vector>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <map>
#include <omp.h>
#include "cnpy.h"
#include "edit_cost/EditCost.h"
#include "graph_loader/GraphLoader.h"
#include "linear_assignment/NodeAssignment.h"

typedef std::map<std::string, Graph> GraphMap;
typedef std::map<std::string, std::vector<std::vector<float>>> EmbeddingMap;


bool custom_sorting(const std::filesystem::path& a, const std::filesystem::path& b) {
    static const std::regex re("graph_(\\d+)\\.graphml");
    std::smatch matchA, matchB;
    
    std::string filenameA = a.filename().string();
    std::string filenameB = b.filename().string();

    if (std::regex_match(filenameA, matchA, re) && std::regex_match(filenameB, matchB, re)) {
        int numA = std::stoi(matchA[1].str());
        int numB = std::stoi(matchB[1].str());
        return numA < numB;
    }
    return filenameA < filenameB;
}

void retrieve_graphs(const std::filesystem::path& graphs_folder, std::vector<std::filesystem::path>& graphs) {
    for (const auto& graph : std::filesystem::directory_iterator(graphs_folder)) {
        graphs.push_back(graph.path());
    }
    std::sort(graphs.begin(), graphs.end(), custom_sorting);
}

bool custom_sorting_emb(const std::filesystem::path& a, const std::filesystem::path& b) {
    static const std::regex re("embedding_(\\d+)\\.npy");
    std::smatch matchA, matchB;
    
    std::string filenameA = a.filename().string();
    std::string filenameB = b.filename().string();

    if (std::regex_match(filenameA, matchA, re) && std::regex_match(filenameB, matchB, re)) {
        int numA = std::stoi(matchA[1].str());
        int numB = std::stoi(matchB[1].str());
        return numA < numB;
    }
    return filenameA < filenameB;
}

void retrieve_embeddings(const std::filesystem::path& embeddings_folder, std::vector<std::filesystem::path>& embeddings) {
    for (const auto& emb : std::filesystem::directory_iterator(embeddings_folder)) {
        embeddings.push_back(emb.path());
    }
    std::sort(embeddings.begin(), embeddings.end(), custom_sorting_emb);
}

void load_graphs_from_directory(const std::vector<std::filesystem::path>& directory, GraphMap& graph_map) {
    GraphLoader G;
    for (const auto& entry : directory) {
        Graph graph;
        G.read_graph(entry, graph);
        graph_map[entry] = graph;
    }
}

void load_embeddings_from_directory(const std::vector<std::filesystem::path>& directory, EmbeddingMap& embedding_map) {
    for (const auto& entry : directory) {
        cnpy::NpyArray arr = cnpy::npy_load(entry);
        int rows1 = arr.shape[0];
        int cols1 = arr.shape[1];
        float* s_embedding = arr.data<float>();
        std::vector<std::vector<float>> embedding(rows1, std::vector<float>(cols1));
        #pragma omp parallel for collapse(2) num_threads(8)
        for (int i = 0; i < rows1; ++i) {
            for (int j = 0; j < cols1; ++j) {
                embedding[i][j] = s_embedding[i * cols1 + j];
            }
        }
        embedding_map[entry] = embedding;
    }
}

void save_matrix_distances(const std::string path, std::vector<std::vector<int>>& matrix_distances) {
    size_t rows = matrix_distances.size();
    size_t cols = matrix_distances[0].size();

    // Convert 2D vector to a contiguous 1D array
    std::vector<size_t> flat_matrix;
    flat_matrix.reserve(rows * cols);
    for (const auto& row : matrix_distances) {
        flat_matrix.insert(flat_matrix.end(), row.begin(), row.end());
    }

    // Define the shape of the array
    std::vector<size_t> shape = { rows, cols };

    // Save the 1D array as a .npy file with the given shape
    cnpy::npy_save(path, &flat_matrix[0], shape, "w");

    std::cout << "File correctly saved!" << std::endl;
}

std::vector<int> load_indices(std::string const& path_idx) {
    cnpy::NpyArray arr = cnpy::npy_load(path_idx);
    int* data = arr.data<int>();
    size_t size = arr.shape[0];
    std::vector<int> vec(data, data + size);
    return vec;
}

void calc_matrix_distances(std::vector<std::vector<int>>& matrix_distances, 
                           const std::vector<int>& train_idx, 
                           const std::vector<int>& test_idx, 
                           const std::vector<std::filesystem::path>& graphs, 
                           const std::vector<std::filesystem::path>& embeddings,
                           GraphMap& graph_map,
                           EmbeddingMap& embedding_map) {
    
    GraphLoader G;
    GraphLoader G1;
    GraphLoader G2;

    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for collapse(2) num_threads(12)
    for (int i = 0; i < test_idx.size(); i++) {

        for (int j = 0; j < train_idx.size(); j++) {

            Graph& g1 = graph_map[graphs[test_idx[i]]];
            Graph& g2 = graph_map[graphs[train_idx[j]]];

            if (G1.get_num_nodes(g1) <= G2.get_num_nodes(g2)) {

                std::vector<std::vector<float>>& source_embedding = embedding_map[embeddings[test_idx[i]]];
                std::vector<std::vector<float>>& target_embedding = embedding_map[embeddings[train_idx[j]]];

                Graph source_graph;
                source_graph = g1;
                Graph target_graph;
                target_graph = g2;

                operations_research::NodeAssignment assignment(source_embedding, target_embedding);

                std::vector<int> node_assignment = assignment.calc_node_assignment();

                EditCost edit_cost(node_assignment, source_graph, target_graph);

                int cost = 0;

                std::vector<int> nodes = G.get_nodes(target_graph);
                std::vector<int> unassigned_nodes(G2.get_num_nodes(g2) - G1.get_num_nodes(g1));
                edit_cost.get_unassigned_nodes(nodes, unassigned_nodes);

                edit_cost.calc_cost_node_edit(cost, unassigned_nodes);

                edit_cost.calc_cost_edge_edit(cost, unassigned_nodes);

                matrix_distances[i][j] = cost;
                
            } else {

                std::vector<std::vector<float>>& source_embedding = embedding_map[embeddings[train_idx[j]]];
                std::vector<std::vector<float>>& target_embedding = embedding_map[embeddings[test_idx[i]]];

                Graph source_graph;
                source_graph = g2;
                Graph target_graph;
                target_graph = g1;

                operations_research::NodeAssignment assignment(source_embedding, target_embedding);

                std::vector<int> node_assignment = assignment.calc_node_assignment();

                EditCost edit_cost(node_assignment, source_graph, target_graph);

                int cost = 0;

                std::vector<int> nodes = G.get_nodes(target_graph);
                std::vector<int> unassigned_nodes(G1.get_num_nodes(g1) - G2.get_num_nodes(g2));
                edit_cost.get_unassigned_nodes(nodes, unassigned_nodes);

                edit_cost.calc_cost_node_edit(cost, unassigned_nodes);

                edit_cost.calc_cost_edge_edit(cost, unassigned_nodes);

                matrix_distances[i][j] = cost;

            }


        }


    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;

}

int main() {
    // TODO: add command line arguments
    std::vector<std::filesystem::path> graphs;
    std::filesystem::path graphs_folder = "/home/dobleraemon/Documents/PhD/graphs/MUTAG/";
    retrieve_graphs(graphs_folder, graphs);

    std::vector<std::filesystem::path> embeddings;
    std::filesystem::path embeddings_folder = "/home/dobleraemon/Documents/PhD/gnn-ged/res/MUTAG/GINv2/raw/embeddings";
    retrieve_embeddings(embeddings_folder, embeddings);

    GraphMap graph_map;
    load_graphs_from_directory(graphs, graph_map);

    EmbeddingMap embedding_map;
    load_embeddings_from_directory(embeddings, embedding_map);

    // MUTAG
    std::string path_train_idx = "/home/dobleraemon/Documents/PhD/gnn-ged/res/MUTAG/train_indices.npy";
    std::string path_test_idx = "/home/dobleraemon/Documents/PhD/gnn-ged/res/MUTAG/test_indices.npy";

    std::vector<int> train_idx = load_indices(path_train_idx);
    std::vector<int> test_idx = load_indices(path_test_idx);
    
    // Initialize matrix distances
    std::vector<std::vector<int>> matrix_distances(test_idx.size(), std::vector<int>(train_idx.size(), 0));

    // Compute GED
    calc_matrix_distances(matrix_distances, train_idx, test_idx, graphs, embeddings, graph_map, embedding_map);

    // Save the results
    // save_matrix_distances("/home/dobleraemon/Documents/PhD/gnn-cppged/res/MUTAG/distances.npy", matrix_distances);

    return 0;
}