#pragma once
#include "DiscreteSpace/Mesh/Mesh.hpp"
#include "BasisFunction/BasisFunction.hpp"
#include "Field.hpp"
#include <memory>

template <size_t dim>
class DiscreteSpace
{
private:
    std::shared_ptr<Mesh<dim>> mesh;
    std::shared_ptr<BasisFunction<dim>> shapeFunction;
    std::shared_ptr<Field> field;

public:
    // constructeur
    DiscreteSpace(std::shared_ptr<Mesh> mesh_, std::shared_ptr<Field> field_, std::shared_ptr<BasisFunction> shapeFunction_);
    // destructeur
    ~DiscreteSpace() = default;
    // method
    const std::shared_ptr<Mesh> &getMesh() const;
    const std::shared_ptr<Field> &getField() const;
    const std::shared_ptr<BasisFunction> &getBasisFunction() const;
    const int getnDofsPerNode() const;

};

