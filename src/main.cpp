// This is the main script that handles everything
#include <string>
#include <regex>
#include <array>
#include <vector>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <map>
#include <omp.h>
#include "cnpy.h"
#include "H5Cpp.h"
#include "edit_cost/EditCost.h"
#include "graph_loader/GraphLoader.h"
#include "linear_assignment/NodeAssignment.h"


typedef std::unordered_map<int, Graph> GraphMap;
typedef std::unordered_map<int, int> NumNodeMap;
typedef std::unordered_map<int, std::vector<int>> NodeMap;
typedef std::unordered_map<int, std::vector<std::vector<float>>> EmbeddingMap;
typedef std::unordered_map<int, std::vector<std::string>> AttributeMap;


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

void load_graphs_from_directory(const std::vector<std::filesystem::path>& directory, GraphMap& graphs) {
    GraphLoader G;
    int i = 0;
    for (const auto& entry : directory) {
        Graph graph;
        G.read_graph(entry, graph);
        graphs[i] = graph;
        // graphs.push_back(graph);
        i++;
    }
}

void load_node_embeddings(const std::string& node_embeddings_path, EmbeddingMap& node_embeddings, int& num_graphs) {
    H5::H5File file(node_embeddings_path, H5F_ACC_RDONLY);

    for (int i = 0; i < num_graphs; ++i) {
        
        std::string dataset_name = "embedding_" + std::to_string(i);
        
        // Try opening the dataset, if it fails, stop the loop (no more arrays)
        H5::DataSet dataset = file.openDataSet(dataset_name);

        // // Get the dataspace and dimensions of the dataset and allocate space for reading
        H5::DataSpace dataspace = dataset.getSpace();
        int rank = dataspace.getSimpleExtentNdims();
        hsize_t dims[2];
        dataspace.getSimpleExtentDims(dims, NULL);
        H5::DataSpace memspace(rank, dims);

        // // Read the data into a C++ vector
        // float data[dims[0]][dims[1]]; // buffer for dataset to be read
        std::vector<float> data(dims[0] * dims[1]);
        
        dataset.read(data.data(), H5::PredType::NATIVE_FLOAT, memspace, dataspace);

        std::vector<std::vector<float>> reshaped_data(dims[0], std::vector<float>(dims[1]));
        for (hsize_t j = 0; j < dims[0]; ++j) {
            for (hsize_t k = 0; k < dims[1]; ++k) {
                reshaped_data[j][k] = data[j * dims[1] + k];
            }
        }

        // // // Add the loaded array to the list of arrays
        // // // node_embeddings.push_back(data);
        node_embeddings[i] = reshaped_data;

        dataset.close();

    }

    file.close();

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

void get_node_info(GraphMap& graphs, NodeMap& nodes, NumNodeMap& num_nodes, AttributeMap& node_attrs, int& num_graphs) {
    GraphLoader G;
    for (int i = 0; i < num_graphs; i++) {
        Graph& g = graphs[i];
        nodes[i] = G.get_nodes(g);
        num_nodes[i] = G.get_num_nodes(g);
        node_attrs[i] = G.get_node_attrs(g);
    }
}

void calc_cost(Graph& source, Graph& target, 
               int& num_nodes_source, int& num_nodes_target, 
               std::vector<std::string>& attrs_source, std::vector<std::string>& attrs_target, 
               int& i, int& j, 
               std::vector<std::vector<int>>& matrix_distances, 
               EmbeddingMap& node_embeddings,
               std::vector<int>& node_assignment,
               std::vector<int>& unassigned_nodes) {
    int cost = 0;
    node_assignment.resize(num_nodes_source);
    unassigned_nodes.resize(num_nodes_target - num_nodes_source);

    operations_research::NodeAssignment assignment(node_embeddings[i], node_embeddings[j]);
    assignment.calc_cost_matrix();
    assignment.linear_assignment(node_assignment);
    // assignment.greedy_assignment(node_assignment);

    EditCost edit_cost(node_assignment, source, target);
    edit_cost.get_unassigned_nodes(num_nodes_target, unassigned_nodes);

    edit_cost.calc_cost_node_edit(cost, num_nodes_source, unassigned_nodes, attrs_source, attrs_target);
    edit_cost.calc_cost_edge_edit(cost, num_nodes_source, unassigned_nodes);

    matrix_distances[i][j] = cost;
}

void calc_matrix_distances(std::vector<std::vector<int>>& matrix_distances,
                           int& num_graphs,
                           GraphMap& graphs,
                           EmbeddingMap& node_embeddings,
                           NodeMap& nodes,
                           NumNodeMap& num_nodes,
                           AttributeMap& node_attrs) {

    GraphLoader G;
    std::vector<int> node_assignment;
    std::vector<int> unassigned_nodes;
    std::vector<int> nodes_g1, nodes_g2;
    std::vector<std::string> attrs_g1, attrs_g2;
    int num_nodes_g1, num_nodes_g2;
    int cost = 0;

    // Reserve sufficient capacity to avoid reallocations in each loop
    int max_num_nodes = std::max_element(num_nodes.begin(), num_nodes.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        })->second;
    
    node_assignment.reserve(max_num_nodes);
    unassigned_nodes.reserve(max_num_nodes);

    // Start the computations
    auto start = std::chrono::high_resolution_clock::now();

    // #pragma omp parallel for num_threads(12) private(cost, node_assignment, unassigned_nodes) collapse(1)
    for (int i = 0; i < num_graphs; i++) {

        Graph& g1 = graphs[i];
        num_nodes_g1 = num_nodes[i];
        attrs_g1 = node_attrs[i];

        for (int j = i + 1; j < num_graphs; j++) {

            Graph& g2 = graphs[j];
            num_nodes_g2 = num_nodes[j];
            attrs_g2 = node_attrs[j];

            if (num_nodes_g1 <= num_nodes_g2) {
                // heuristic -> the smaller graph is always the source graph
                calc_cost(g1, g2, num_nodes_g1, num_nodes_g2, attrs_g1, attrs_g2, i, j, matrix_distances, node_embeddings, node_assignment, unassigned_nodes);
                
            } else {
                
                calc_cost(g2, g1, num_nodes_g2, num_nodes_g1, attrs_g2, attrs_g1, j, i, matrix_distances, node_embeddings, node_assignment, unassigned_nodes);

            }

        }

    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " microseconds" << std::endl;
    
}

int main(int argc, char* argv[]) {
    
    // Get command line arguments
    std::filesystem::path graphs_folder = argv[1];
    std::string node_embeddings_path = argv[2];
    std::string output_path = argv[3];

    // Preprocess
    std::vector<std::filesystem::path> graphs_files;
    retrieve_graphs(graphs_folder, graphs_files);

    int num_graphs = graphs_files.size();

    GraphMap graphs;
    load_graphs_from_directory(graphs_files, graphs);

    EmbeddingMap node_embeddings;
    load_node_embeddings(node_embeddings_path, node_embeddings, num_graphs);

    NodeMap nodes;
    NumNodeMap num_nodes;
    AttributeMap node_attrs;
    get_node_info(graphs, nodes, num_nodes, node_attrs, num_graphs);

    // Initialize the matrix of distances
    std::vector<std::vector<int>> matrix_distances(num_graphs, std::vector<int>(num_graphs, 0));

    // Compute GED
    calc_matrix_distances(matrix_distances, num_graphs, graphs, node_embeddings, nodes, num_nodes, node_attrs);

    // Save the results
    save_matrix_distances(output_path, matrix_distances);

    return 0;
}