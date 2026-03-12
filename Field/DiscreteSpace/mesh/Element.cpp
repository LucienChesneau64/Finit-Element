#include "Element.hpp"


template <size_t dim>
Element<dim>::Element(const std::array<int, dim + 1> &ids)
    : nodeIds(ids) {}

const std::array<int, dim + 1> &Element::getNodeIds() const
{
    return nodeIds;
}

template <size_t dim>
double Element<dim>::computeArea(const std::vector<Nodes> &allNodes) const
{
    // ALlnodes = le vecteur noeud du mesh.
    int n1 = allNodes[nodeIds[0]];
    int n2 = allNodes[nodeIds[1]];
    int n3 = allNodes[nodeIds[2]];

    double area;
    // appliquer formule air pour triangle.

    return area;
}
