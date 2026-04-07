#ifndef MASS_OPERATOR_HPP
#define MASS_OPERATOR_HPP

#include "physics/Operators/BilinearOperator/IBilinearOperator.hpp"

/**
 * @brief Opérateur de Masse : \int u * v
 * Utilisé pour les termes instationnaires (M * du/dt) ou les forces de volume.
 */
template <size_t dim>
class MassOperator : public IBilinearOperator<dim> {
private:
    double density_; // Coefficient multiplicateur (ex: rho)

public:
    explicit MassOperator(double density = 1.0) 
        : density_(density) {}

protected:
    /**
     * @brief Implémentation du cœur : rho * phi_j * phi_i
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