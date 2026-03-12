#pragma once
#include <vector>
#include <string>
#include "Node.hpp"
#include "Element.hpp"

template <size_t dim>
class Mesh
{
private:
    std::vector<Node<dim>> nodes;
    std::vector<Element<dim>> elements;
    int nNodes;

public:
    Mesh() = default;
    explicit Mesh(const std::string &path);

    const std::vector<Node<dim>> &getNodes() const;
    const std::vector<Element<dim>> &getElements() const;
    void calculatenNodes();
    const int getnNodes() const;


    void loadFromFile(const std::string &path);
};