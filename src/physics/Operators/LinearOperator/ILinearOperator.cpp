#ifndef ILINEAR_OPERATOR_CPP
#define ILINEAR_OPERATOR_CPP

#include "physics/Operators/LinearOperator/ILinearOperator.hpp"
#include "core/FE/basisfunction/Quadrature.hpp"
#include <cmath>

template <size_t dim>
Eigen::VectorXd ILinearOperator<dim>::computeLocalVector(
    const Element<dim>& el, 
    const DiscreteSpace<dim>& spaceTest) const 
{
    // 1. Détermination de la taille (ex: 3 pour un triangle P1)
    // On accède à la shapeFunction via l'espace de test
    int nRows = spaceTest.shapeFunction().getNbDofsPerElement();
    Eigen::VectorXd bk = Eigen::VectorXd::Zero(nRows);

    // 2. Initialisation de la quadrature (Ordre 2 pour du P1)
    // On l'instancie ici pour que l'opérateur maîtrise sa précision
    Quadrature<dim> quadrature(2); 

    // 3. Calcul de la Jacobienne (constante pour des éléments P1)
    // On récupère les nœuds via le maillage associé à l'espace
    const auto& allNodes = spaceTest.mesh().getNodes();
    double detJ = el.computeJacobian(allNodes).determinant();
    double absDetJ = std::abs(detJ);

    // 4. Boucle d'intégration numérique (Somme de Gauss)
    for (const auto& qp : quadrature.getPoints()) 
    {
        double weight = qp.weight() * absDetJ;

        for (int i = 0; i < nRows; ++i) {
            // Appel de la fonction virtuelle pure implémentée dans les classes filles
            // C'est ici que l'utilisateur définit son f(x)
            bk(i) += evalKernel(spaceTest, qp, el, i) * weight;
        }
    }

    return bk;
}

// Instanciations explicites pour le linker
template class ILinearOperator<2>;
template class ILinearOperator<3>;

#endif