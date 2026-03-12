#include "Equation.hpp"

Equation::Equation() {};


// modif avec discreteSpace.
// enlever getDof().
// créer le globalDofHandler ici à partir du multiField.
// rentrer le globalDofHandler qui est créer au départ dans run ou stable. 

Eigen::SparseMatrix<double> Equation::assembleStiffMatrix(const DiscreteSpace &discreteSpace)
{
    auto dof = discreteSpace.getDof();
    Eigen::SparseMatrix<double> A(dof->nIndexs(), dof->nIndexs());
    for (const auto &bf : bilinearForms)
    {
        bf->assemble(discreteSpace, A);
    }
    return A;
}
// assemble a changer. prends en argument deux espaceDiscrets // revoir...
// changer assembleA en assembleStiffnesMatrix()

Eigen::VectorXd Equation::assembleb(const DiscreteSpace &discreteSpace)
{
    auto dof = discreteSpace.getDof();
    Eigen::VectorXd b = Eigen::VectorXd::Zero(dof->nIndexs());
    for (const auto &lf : linearForms)
    {
        lf->assemble(discreteSpace, b);
    }
    return b;
}

// ajout de assembleMassMatrix -> fait appel a classe héritée de linearform.hpp
// step prendra StiffMatrix, MassMatrix en argument avec


// assembleb a changé aussi. 


