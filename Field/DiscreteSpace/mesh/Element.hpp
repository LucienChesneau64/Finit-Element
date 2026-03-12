#pragma once
#include <vector>
#include "Nodes.hpp"
#include "Quadrature.hpp"


// ajout classe quadrature dans élément.

template <size_t dim>

class Element
{
private:
    std::array<int, dim + 1> nodeIds;
    Quadrature quadrature;

public:
    explicit Element(const std::array<int, dim + 1> &ids);

    const std::array<int, dim + 1> &getNodeIds() const;

    // area
    double computeArea(const std::vector<Nodes> &allNodes) const;
    // on doit obtenir les noeuds et leurs positions. pour pouvoir calculer l'air du triangle.
    
    // pour se faire on doit donc les chercher.
    Quadrature getQuadrature();
};

