#include "Mesh.hpp"

Mesh::Mesh(const std::string& path) {
    loadFromFile(path);
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

