#pragma once
#include <Eigen/Sparse>
#include "DiscreteSpace.hpp"

template <siz_t dim>

// doit prendre en membre privé la classe quadrature, c'est ce qui intègre.
// dans l'ordre 
// méthode assemble, boucle sur les éléments et calcule méthode matrixLocal(element), et les distribue sur la matrixGlobal.
//  doit prendre GlobalDofHandler en argument + multifield...
//      methode matrixLocal(element, discretspace1, discretSpace2): -> calcul les evalKernel(i,j)
//          methode virtuel evalKernel(i,j).




class BilinearForm
{
public:
    virtual ~BilinearForm() = default;

    void assemble(); // voir a passer avec quoi.. . . . 

    Eigen::MatrixXd computeLocalMatrix(
        const Element& element, 
        const DiscreteSpace& spaceTest, 
        const DiscreteSpace& spaceTrial)
    ; 
    // calcul la matrice local de l'opérateur bilinéaire. 
    // bilinéaire car prend les deux espaces.
    // 

    virtual double localContribution(
        const DiscreteSpace<dim> &discreteSpace,
        const Element<dim> &e,
        int local_i,
        int local_j)
        const = 0;
};


// revoir pour ajout du dofHandler
// refactoring localContribution.
// on prend localContribution(element)
// calcul matrice locale Ak
// puis assemble dans la matrice globale avec Ak
// on appelle ici le dofHandler.




// changer pour logique P1 - Pn
Eigen::MatrixXd computeLocalMatrix(const Element& el, 
                                   const DiscreteSpace& spaceTest, 
                                   const DiscreteSpace& spaceTrial) {
    
    int nDofsTest = spaceTest.getnDofsPerElement();
    int nDofsTrial = spaceTrial.getnDofsPerElement();
        
    Eigen::MatrixXd Ak = Eigen::MatrixXd::Zero(nDofsTest, nDofsTrial);

        // obtient quadrature via elements.



        // Boucle de quadrature        
    for (const auto& qPoint : quadrature.points()) {
        auto phi_test = spaceTest.basisFunctions(qPoint, el); // ex: fonctions pour la pression
        auto phi_trial = spaceTrial.basisFunctions(qPoint, el); // ex: fonctions pour la vitesse
            
        double weight = qPoint.weight() * el.detJacobian(qPoint);

        for (int i = 0; i < nDofsTest; ++i) {
            for (int j = 0; j < nDofsTrial; ++j) {
                    // methode virtuel evalkernel

                    // par exmple pour q*div(u)
                    //Ak(i, j) += phi_test[i] * div(phi_trial[j]) * weight;
            }            
        }
    }
    return Ak;
}



