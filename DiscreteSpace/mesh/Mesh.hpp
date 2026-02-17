#pragma once
#include <vector>
#include <string>
#include "Node.hpp"
#include "Element.hpp"

class Mesh {
private:
    std::vector<Node> nodes;
    std::vector<Element<dim>> elements;

public:
    Mesh() = default;
    explicit Mesh(const std::string& path);

    const std::vector<Node>& getNodes() const;
    const std::vector<Element>& getElements() const;

    void loadFromFile(const std::string& path);
};


