#include "BilinearForm.hpp"

void BilinearForm::assemble(
    const DiscreteSpace<dim>& discreteSpace,
    Eigen::SparseMatrix<double>& A) const {
    
    // les multifields vivent sur le meme mesh.
    // getMesh, getDof, getBasisFunction
    // changer ca pour multifield.
    // ajuster en dim
    // ajuster pour accueillir les degree of freedom.
    

    auto& mesh = discreteSpace.getMesh();
    auto& index = discreteSpace.getDof();
    auto& basisFunction = discreteSpace.getBasisFunction();

    for (const auto& elem : mesh->getElements()) {
        const auto& ids = elem.getNodeIds();

        for (int a = 0; a < 3; ++a) {
            int i = index->Index(ids[a]);
            for (int b = 0; b < 3; ++b) {
                int j = index->dof(ids[b]);
                A.coeffRef(i,j) += localContribution(discreteSpace ,elem, a, b);
            }
        }
    }
}

// changer ici pour dim avec template. les boucles for. 


//int nLocalDofs = basisFunction->nLocalDofs(elem);
//for (int a = 0; a < nLocalDofs; ++a)

// changer pour logique P1 - Pn
Eigen::MatrixXd computeLocalMatrix(const Element& el, 
                                   const DiscreteSpace& spaceTest, 
                                   const DiscreteSpace& spaceTrial) {
    
        int nDofsTest = spaceTest.getnDofsPerElement();
        int nDofsTrial = spaceTrial.getnDofsPerElement();
        
        Eigen::MatrixXd Ak = Eigen::MatrixXd::Zero(nDofsTest, nDofsTrial);

        // Boucle de quadrature
        for (const auto& qPoint : quadrature.points()) {
            auto phi_test = spaceTest.basisFunctions(qPoint, el); // ex: fonctions pour la pression
            auto phi_trial = spaceTrial.basisFunctions(qPoint, el); // ex: fonctions pour la vitesse
            
            double weight = qPoint.weight() * el.detJacobian(qPoint);

            for (int i = 0; i < nDofsTest; ++i) {
                for (int j = 0; j < nDofsTrial; ++j) {
                    // C'est ICI qu'on définit le lien !
                    // Exemple pour q * div(u) :
                    // methode virtuel localContribution:

                    //Ak(i, j) += phi_test[i] * div(phi_trial[j]) * weight;
                }
            }
        }
        return Ak;
    }
};

