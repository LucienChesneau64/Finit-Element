#include "core/Geometry/Mesh.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <set>

template <size_t dim>
Mesh<dim>::Mesh() : nNodes_(0) {}

template <size_t dim>
Mesh<dim>::Mesh(const std::string& path) : nNodes_(0) {
    loadFromFile(path);
}

template <size_t dim>
const std::vector<Node<dim>>& Mesh<dim>::getNodes() const { return nodes_; }

template <size_t dim>
const std::vector<Element<dim>>& Mesh<dim>::getElements() const { return elements_; }

template <size_t dim>
int Mesh<dim>::getNNodes() const { return static_cast<int>(nodes_.size()); }

template <size_t dim>
void Mesh<dim>::loadFromFile(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("[Mesh] Erreur : Impossible d'ouvrir " + path);
    }

    // Nettoyage complet avant recharge
    nodes_.clear();
    elements_.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("$Nodes") != std::string::npos) {
            int numNodes;
            if (!(file >> numNodes)) continue;

            nodes_.reserve(numNodes);
            for (int i = 0; i < numNodes; ++i) {
                int id;
                double x, y, z;
                file >> id >> x >> y >> z;

                std::array<double, dim> coords;
                coords[0] = x;
                if constexpr (dim >= 2) coords[1] = y;
                if constexpr (dim == 3) coords[2] = z;

                nodes_.emplace_back(id - 1, coords);
            }
        } 
        else if (line.find("$Elements") != std::string::npos) {
            int numElements;
            if (!(file >> numElements)) continue;

            elements_.reserve(numElements);
            for (int i = 0; i < numElements; ++i) {
                int id, type, nTags;
                file >> id >> type >> nTags;

                std::vector<int> tags(nTags);
                for (int j = 0; j < nTags; ++j) file >> tags[j];
                
                // Le Physical ID est le premier tag dans GMSH 2.2
                int physicalId = (nTags > 0) ? tags[0] : 0;

                int nodesPerElement = 0;
                if (type == 1) nodesPerElement = 2;      // Line
                else if (type == 2) nodesPerElement = 3; // Triangle
                else if (type == 4) nodesPerElement = 4; // Tetra

                std::vector<int> nodeIndices;
                for (int j = 0; j < nodesPerElement; ++j) {
                    int nodeId;
                    file >> nodeId;
                    nodeIndices.push_back(nodeId - 1);
                }

                if (nodesPerElement > 0) {
                    elements_.emplace_back(type, physicalId, nodeIndices);
                }
            }
        }
    }
    nNodes_ = static_cast<int>(nodes_.size());

    if (nNodes_ == 0) {
        throw std::runtime_error("[Mesh] Erreur fatale : Aucun noeud chargé depuis " + path);
    }

    std::cout << "[Mesh] " << path << " charge avec succes : " 
              << nNodes_ << " noeuds, " 
              << elements_.size() << " elements." << std::endl;
}

template <size_t dim>
std::vector<int> Mesh<dim>::getNodesOnBoundary(int boundaryId) const {
    std::set<int> uniqueNodes;
    for (const auto& el : elements_) {
        // En 2D, les bords sont de type 1 (Line). 
        // En 3D, les bords sont de type 2 (Triangle).
        int boundaryType = (dim == 2) ? 1 : 2;

        if (el.getType() == boundaryType && el.getPhysicalId() == boundaryId) {
            for (int nodeIdx : el.getNodeIndices()) {
                uniqueNodes.insert(nodeIdx);
            }
        }
    }
    return std::vector<int>(uniqueNodes.begin(), uniqueNodes.end());
}

template class Mesh<2>;
template class Mesh<3>;