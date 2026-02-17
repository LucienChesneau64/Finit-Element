#include "DiscreteSpace.hpp"

DiscreteSpace::DiscreteSpace(std::shared_ptr<Mesh> mesh_, std::shared_ptr<IndexHandler> dof_, std::shared_ptr<BasisFunction> shapeFunction_): mesh(mesh_), dof(dof_), shapeFunction(shapeFunction_)
{
}

std::shared_ptr<BasisFunction> DiscreteSpace::getBasisFunction() const {
    return shapeFunction;
}

std::shared_ptr<Mesh> DiscreteSpace::getMesh() const {
    return mesh;
}

std::shared_ptr<IndexHandler> DiscreteSpace::getDof() const {
    return dof;
}

