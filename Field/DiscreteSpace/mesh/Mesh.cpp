#include "Mesh.hpp"

Mesh::Mesh(const std::string& path) {
    loadFromFile(path);
    calculatenNodes();
}

void Mesh::calculatenNodes() [
    // calculate Number of Nodes in mesh.
]

int Mesh::getnNodes() {
    return nNodes;
}

void Mesh::loadFromFile(const std::string& path) {
    // TODO: gmsh / mesh reader
}

const std::vector<Node>& Mesh::getNodes() const {
    return nodes;
}

const std::vector<Element>& Mesh::getElements() const {
    return elements;
}


