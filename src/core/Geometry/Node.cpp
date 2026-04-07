#include "core/Geometry/Node.hpp"

template <size_t dim>
Node<dim>::Node() : id_(-1) {
    coords_.fill(0.0);
}

template <size_t dim>
Node<dim>::Node(int id, const std::array<double, dim>& coords) 
    : id_(id), coords_(coords) {}

template <size_t dim>
int Node<dim>::getId() const { 
    return id_; 
}

template <size_t dim>
const std::array<double, dim>& Node<dim>::getCoords() const { 
    return coords_; 
}

template <size_t dim>
double Node<dim>::operator[](size_t i) const { 
    return coords_[i]; 
}

// Instanciations explicites pour 1D, 2D et 3D
template class Node<1>;
template class Node<2>;
template class Node<3>;

