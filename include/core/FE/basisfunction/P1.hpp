#ifndef CORE_FE_BASISFUNCTION_P1_HPP
#define CORE_FE_BASISFUNCTION_P1_HPP

#include <Eigen/Dense>
#include "core/FE/basisfunction/BasisFunction.hpp"
#include "core/FE/basisfunction/QuadraturePoint.hpp"

/**
 * @brief Fonctions de base de Lagrange de degré 1 (P1).
 * Valide pour Segment (1D), Triangle (2D) et Tétraèdre (3D).
 */
template <size_t dim>
class P1 : public BasisFunction<dim> {
public:
    P1();

    /**
     * @brief Évalue la i-ème fonction de forme au point qp.
     */
    double evaluate(int i, const QuadraturePoint<dim>& qp) const override;

    /**
     * @brief Évalue le gradient LOCAL (d_phi/d_xi) sur l'élément de référence.
     * Le passage au gradient réel se fait dans l'Opérateur via la Jacobienne.
     */
    Eigen::Vector<double, dim> evaluateLocalGradient(int i, const QuadraturePoint<dim>& qp) const override;
};

#endif
