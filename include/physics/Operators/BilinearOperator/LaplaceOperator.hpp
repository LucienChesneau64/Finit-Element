#ifndef PHYSICS_OPERATORS_BILINEAR_OPERATOR_LAPLACE_OPERATOR_HPP
#define PHYSICS_OPERATORS_BILINEAR_OPERATOR_LAPLACE_OPERATOR_HPP

#include "physics/Operators/BilinearOperator/IBilinearOperator.hpp"

/**
 * @brief Opérateur de Laplace : \int \nabla u \cdot \nabla v
 * Utilisé pour la diffusion, la thermique, l'électrostatique, etc.
 */
template <size_t dim>
class LaplaceOperator : public IBilinearOperator<dim> {
private:
    double diffusivity_; // Coefficient k ou alpha (ex: conductivité thermique)

public:
    explicit LaplaceOperator(double diffusivity = 1.0) 
        : diffusivity_(diffusivity) {}

protected:
    /**
     * @brief Implémentation du cœur mathématique : k * grad(phi_j) . grad(phi_i)
     */
    double evalKernel(
        const DiscreteSpace<dim>& spaceTest,
        const DiscreteSpace<dim>& spaceTrial,
        const QuadraturePoint<dim>& qp,
        const Element<dim>& el,
        int i, int j
    ) const override;
};

#endif
