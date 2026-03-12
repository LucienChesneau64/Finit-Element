#include "DiscreteSpace.hpp"

DiscreteSpace::DiscreteSpace(std::shared_ptr<Mesh> mesh_, std::shared_ptr<Field> field_, std::shared_ptr<BasisFunction> shapeFunction_): mesh(mesh_), field(field_), shapeFunction(shapeFunction_)
{
}


std::shared_ptr<BasisFunction> DiscreteSpace::getBasisFunction() const {
    return shapeFunction;
}

std::shared_ptr<Mesh> DiscreteSpace::getMesh() const {
    return mesh;
}

std::shared_ptr<Field> DiscreteSpace::getField() const {
    return dof;
}


int getnDofPerNodes() const {
    return field->getnComponent() * shapeFunction->getnDof();
}

