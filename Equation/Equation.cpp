#include "Equation.hpp"

Equation::Equation() {};

Eigen::SparseMatrix<double> Equation::assembleStiffMatrix(const DiscreteSpace& discreteSpace) {
    auto dof = discreteSpace.getDof();
    Eigen::SparseMatrix<double> A(dof->nIndexs(), dof->nIndexs());
    for (const auto& bf : bilinearForms) {
        bf->assemble(discreteSpace, A);
    }
    return A;
}
// changer assembleA en assembleStiffnesMatrix()

Eigen::VectorXd Equation::assembleb(const DiscreteSpace& discreteSpace) {
    auto dof = discreteSpace.getDof();
    Eigen::VectorXd b = Eigen::VectorXd::Zero(dof->nIndexs());
    for (const auto& lf : linearForms) {
        lf->assemble(discreteSpace, b);
    }
    return b;
}

// ajout de assembleMassMatrix -> fait appel a classe hérité de linearform.hpp
// step prendra StiffMatrix, MassMatrix en argument avec 

