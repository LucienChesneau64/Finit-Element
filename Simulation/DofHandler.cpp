#include "DofHandler.hpp"

template <size_t dim>
void DofHandler<dim>::distributeDofHandler(const DiscreteSpace<dim>& space) {

    int nNodes = space.getMesh().getnNodes();
    
    this->nDofsPerNode_ = space.getnDofsPerNode(); 

    this->nDofs_ = nNodes * this->nDofsPerNode_;
    
    // attribue en mémoire contigue.

}

template <size_t dim>
int DofHandler<dim>::Dof(int nodeId) const {
    return nodeId * nDofsPerNode_;
    }


template <size_t dim>
int DofHandler<dim>::Dof(int nodeId, int componentId) const {
    return (nodeId * nDofsPerNode_) + componentId;
}
