#include "DiscreteSpace.hpp"

template <size_t dim>

DiscreteSpace::DiscreteSpace(
    std::shared_ptr<Mesh<dim>> mesh_,
    std::shared_ptr<Field> field_,
    std::shared_ptr<BasisFunction<dim>> shapeFunction_):
    mesh(mesh_),
    field(field_),
    shapeFunction(shapeFunction_) {}

std::shared_ptr<BasisFunction> DiscreteSpace::getBasisFunction() const {
    return shapeFunction;
}

std::shared_ptr<Mesh<dim>> DiscreteSpace::getMesh() const {
    return mesh;
}

std::shared_ptr<Field> DiscreteSpace::getField() const {
    return dof;
}

