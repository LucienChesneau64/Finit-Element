#ifndef PHYSICS_OPERATORS_BILINEAR_OPERATOR_IBILINEAR_OPERATOR_HPP
#define PHYSICS_OPERATORS_BILINEAR_OPERATOR_IBILINEAR_OPERATOR_HPP

#include <Eigen/Dense>
#include "core/Space/DiscreteSpace.hpp"
#include "core/FE/basisfunction/QuadraturePoint.hpp"
#include "core/Geometry/Element.hpp"

/**
 * @brief Interface pour tout opérateur bilinéaire (intégrale de deux fonctions).
 */
template <size_t dim>
class IBilinearOperator {
public:
    virtual ~IBilinearOperator() = default;

    /**
     * @brief Gère la boucle de quadrature pour remplir la matrice locale Ak.
     */
    Eigen::MatrixXd computeLocalMatrix(
        const Element<dim>& el, 
        const DiscreteSpace<dim>& spaceTest, 
        const DiscreteSpace<dim>& spaceTrial
    ) const;

protected:
    /**
     * @brief La "physique" de l'opérateur (ex: grad(phi_i) * grad(phi_j)).
     */
    virtual double evalKernel(
        const DiscreteSpace<dim>& spaceTest,
        const DiscreteSpace<dim>& spaceTrial,
        const QuadraturePoint<dim>& qp,
        const Element<dim>& el,
        int i, 
        int j
    ) const = 0;
};

#endif