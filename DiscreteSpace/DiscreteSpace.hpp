#pragma once
#include "DiscreteSpace/Mesh/Mesh.hpp"
#include "BasisFunction/BasisFunction.hpp"
#include "IndexHandler.hpp"
#include <memory>

class DiscreteSpace {
    private:
        std::shared_ptr<Mesh> mesh;
        std::shared_ptr<IndexHandler> dof;
        std::shared_ptr<BasisFunction> shapeFunction;
    public:
        // constructeur
        DiscreteSpace(std::shared_ptr<Mesh> mesh_, std::shared_ptr<IndexHandler> dof_, std::shared_ptr<BasisFunction> shapeFunction_);
        // destructeur
        ~DiscreteSpace() = default;
        // method
        const std::shared_ptr<Mesh>& getMesh() const;
        const std::shared_ptr<IndexHandler>& getDof() const;
        const std::shared_ptr<BasisFunction>& getBasisFunction() const;
};


