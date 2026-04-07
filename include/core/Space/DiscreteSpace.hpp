#ifndef CORE_SPACE_DISCRETE_SPACE_HPP
#define CORE_SPACE_DISCRETE_SPACE_HPP

#include <memory>
#include "core/Geometry/Mesh.hpp"
#include "core/FE/basisfunction/BasisFunction.hpp"
#include "core/Space/LocalMapper.hpp"

/**
 * @brief Définit l'espace d'approximation (Maillage + Type d'élément).
 */
template <size_t dim>
class DiscreteSpace {
private:
    std::shared_ptr<const Mesh<dim>> mesh_;
    std::shared_ptr<BasisFunction<dim>> shapeFunction_;
    LocalMapper mapper_;
    int dofsPerNode_; 

public:
    DiscreteSpace(std::shared_ptr<const Mesh<dim>> mesh, 
                  std::shared_ptr<BasisFunction<dim>> shapeFunction,
                  int dofsPerNode = 1);

    ~DiscreteSpace() = default;

    // Getters
    const LocalMapper& getMapper() const;
    const Mesh<dim>& mesh() const;
    const BasisFunction<dim>& shapeFunction() const;
    int getDofsPerNode() const;
    int getNbTotalDofs() const;
};

#endif

