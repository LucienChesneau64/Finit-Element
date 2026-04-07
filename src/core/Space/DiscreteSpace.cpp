#include "core/Space/DiscreteSpace.hpp"

template <size_t dim>
DiscreteSpace<dim>::DiscreteSpace(std::shared_ptr<const Mesh<dim>> mesh, 
                                  std::shared_ptr<BasisFunction<dim>> shapeFunction,
                                  int dofsPerNode)
    : mesh_(mesh), shapeFunction_(shapeFunction), dofsPerNode_(dofsPerNode) 
{
    // On initialise le mapper interne ici
    mapper_.build(mesh_->getNNodes(), dofsPerNode_);
}

template <size_t dim>
const Mesh<dim>& DiscreteSpace<dim>::mesh() const { 
    return *mesh_; 
}

template <size_t dim>
const BasisFunction<dim>& DiscreteSpace<dim>::shapeFunction() const { 
    return *shapeFunction_; 
}

template <size_t dim>
const LocalMapper& DiscreteSpace<dim>::getMapper() const {
    return mapper_;
}

template <size_t dim>
int DiscreteSpace<dim>::getDofsPerNode() const { 
    return dofsPerNode_; 
}

template <size_t dim>
int DiscreteSpace<dim>::getNbTotalDofs() const {
    return mapper_.nTotalDofs(); // Plus propre d'utiliser le mapper directement
}

// Instanciations explicites
template class DiscreteSpace<2>;
template class DiscreteSpace<3>;