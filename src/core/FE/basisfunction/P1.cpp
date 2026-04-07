#include "core/FE/basisfunction/P1.hpp"
#include <stdexcept>

template <size_t dim>
P1<dim>::P1() : BasisFunction<dim>(dim + 1) {} // dim+1 DOFs (3 pour 2D, 4 pour 3D)

template <size_t dim>
double P1<dim>::evaluate(int i, const QuadraturePoint<dim>& qp) const {
    // Coordonnées barycentriques sur le simplexe de référence
    // Phi_0 = 1 - xi_1 - xi_2 (- xi_3)
    // Phi_1 = xi_1
    // Phi_2 = xi_2 ...

    if (i == 0) {
        double val = 1.0 - qp.point()(0);
        if constexpr (dim > 1) val -= qp.point()(1);
        if constexpr (dim > 2) val -= qp.point()(2);
        return val;
    } 
    
    // Pour i > 0, on renvoie simplement la coordonnée correspondante
    if (i >= 1 && i <= (int)dim) {
        return qp.point()(i - 1);
    }
    
    throw std::out_of_range("Indice de fonction de forme P1 invalide pour la dimension choisie.");
}

template <size_t dim>
Eigen::Vector<double, dim> P1<dim>::evaluateLocalGradient(int i, const QuadraturePoint<dim>& /*qp*/) const {
    // Le gradient local (dans l'élément de référence) est constant pour du P1
    Eigen::Vector<double, dim> localGrad = Eigen::Vector<double, dim>::Zero();

    if (i == 0) {
        // Dérivée de (1 - r - s) -> [-1, -1]
        localGrad.setConstant(-1.0);
    } else if (i >= 1 && i <= (int)dim) {
        // Dérivée de r -> [1, 0], dérivée de s -> [0, 1]
        localGrad(i - 1) = 1.0;
    } else {
        throw std::out_of_range("Indice de gradient P1 invalide.");
    }

    return localGrad;
}

// Instanciations explicites pour le linker
template class P1<2>;
template class P1<3>;