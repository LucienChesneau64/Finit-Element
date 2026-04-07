#ifndef CORE_FE_BASISFUNCTION_BASISFUNCTION_HPP
#define CORE_FE_BASISFUNCTION_BASISFUNCTION_HPP

#include <Eigen/Dense>
// On inclut le QuadraturePoint car on évalue aux points d'intégration
#include "core/FE/basisfunction/QuadraturePoint.hpp" 

template <size_t dim>
class BasisFunction {
protected:
    int nDofsPerElement_; 

public:
    explicit BasisFunction(int nDofs) : nDofsPerElement_(nDofs) {}
    virtual ~BasisFunction() = default;

    /**
     * @brief Évalue phi_i au point de quadrature (dans l'élément de référence).
     */
    virtual double evaluate(int i, const QuadraturePoint<dim>& qp) const = 0;

    /**
     * @brief Renvoie le gradient LOCAL (d_phi / d_xi) au point de quadrature.
     * On ne passe plus la Jacobienne ici ! 
     * C'est l'appelant qui fera : grad_reel = inv(J)^T * grad_local
     */
    virtual Eigen::Vector<double, dim> evaluateLocalGradient(int i, 
                                                             const QuadraturePoint<dim>& qp) const = 0;

    int getNbDofsPerElement() const { return nDofsPerElement_; }
};

#endif