#ifndef PHYSICS_OPERATORS_LINEAR_OPERATOR_ILINEAR_OPERATOR_HPP
#define PHYSICS_OPERATORS_LINEAR_OPERATOR_ILINEAR_OPERATOR_HPP

#include <Eigen/Dense>
#include "core/Space/DiscreteSpace.hpp"
#include "core/FE/basisfunction/QuadraturePoint.hpp"
#include "core/Geometry/Element.hpp"

/**
 * @brief Interface pour tout opérateur linéaire (ex: Terme source, Gravité).
 * Calcule le vecteur local bk = \int (f * phi_i) dV
 */
template <size_t dim>
class ILinearOperator {
public:
    virtual ~ILinearOperator() = default;

    /**
     * @brief Calcule le vecteur local bk pour un élément donné.
     */
    Eigen::VectorXd computeLocalVector(
        const Element<dim>& el, 
        const DiscreteSpace<dim>& spaceTest
    ) const;

protected:
    /**
     * @brief Cœur mathématique : définit la fonction à intégrer.
     * @param spaceTest L'espace des fonctions de test.
     * @param qPoint Le point de quadrature actuel.
     * @param el L'élément courant.
     * @param i Indice local du DDL de test.
     */
    virtual double evalKernel(
        const DiscreteSpace<dim>& spaceTest,
        const QuadraturePoint<dim>& qPoint,
        const Element<dim>& el,
        int i
    ) const = 0;
};

#endif