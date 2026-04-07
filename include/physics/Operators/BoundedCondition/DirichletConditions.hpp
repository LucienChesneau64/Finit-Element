#ifndef PHYSICS_OPERATORS_BOUNDED_CONDITION_DIRICHLET_CONDITIONS_HPP
#define PHYSICS_OPERATORS_BOUNDED_CONDITION_DIRICHLET_CONDITIONS_HPP

#include "physics/Operators/BoundedCondition/BoundaryCondition.hpp"
/**
 * @brief Condition de Dirichlet forte : u = g sur le bord Gamma.
 */
template <size_t dim>
class DirichletConditions : public BoundaryCondition<dim> {
private:
    double value_; // La valeur imposée (g)

public:
    DirichletConditions(int fieldId, int boundaryId, double value)
        : BoundaryCondition<dim>(fieldId, boundaryId), value_(value) {}

    /**
     * @brief Applique la condition en modifiant A et b.
     */
    void apply(Eigen::SparseMatrix<double>& A, 
               Eigen::VectorXd& b, 
               const MultiField<dim>& mf) const override;
};

#endif