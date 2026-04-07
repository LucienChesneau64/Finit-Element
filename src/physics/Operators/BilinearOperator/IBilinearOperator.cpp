#include "physics/Operators/BilinearOperator/IBilinearOperator.hpp"
#include "core/FE/basisfunction/Quadrature.hpp"
#include <cmath>

template <size_t dim>
Eigen::MatrixXd IBilinearOperator<dim>::computeLocalMatrix(
    const Element<dim>& el, 
    const DiscreteSpace<dim>& spaceTest, 
    const DiscreteSpace<dim>& spaceTrial) const 
{
    // 1. Taille de la matrice (ex: 3x3 pour P1 en 2D)
    int nRows = spaceTest.shapeFunction().getNbDofsPerElement();
    int nCols = spaceTrial.shapeFunction().getNbDofsPerElement();
    
    Eigen::MatrixXd Ak = Eigen::MatrixXd::Zero(nRows, nCols);

    // 2. Choix de la quadrature (Ordre 2 par défaut pour du P1)
    Quadrature<dim> quadrature(2); 

    // Pré-calcul de la Jacobienne (constante pour des éléments P1)
    // On le fait une seule fois hors de la boucle i,j pour gagner en perf
    double detJ = std::abs(el.computeJacobian(spaceTest.mesh().getNodes()).determinant());

    // 3. Boucle d'intégration numérique
    for (const auto& qp : quadrature.getPoints()) 
    {
        double weight = qp.weight() * detJ;

        for (int i = 0; i < nRows; ++i) {
            for (int j = 0; j < nCols; ++j) {
                // Injection de la physique
                double kernelVal = evalKernel(spaceTest, spaceTrial, qp, el, i, j);
                Ak(i, j) += kernelVal * weight;
            }
        }
    }

    return Ak;
}

// Instanciations explicites
template class IBilinearOperator<2>;
template class IBilinearOperator<3>;