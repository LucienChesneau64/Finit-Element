#include "Equation.hpp"

Equation::Equation() {};

Eigen::SparseMatrix<double> Equation::assembleA(const DiscreteSpace& discreteSpace) {
    // get dof and mesh.
    auto dof = discreteSpace.getDof();
    Eigen::SparseMatrix<double> A(dof->nIndexs(), dof->nIndexs());
    for (const auto& bf : bilinearForms) {
        bf->assemble(discreteSpace, A);
    }
    return A;
}

// prendre en entrée dans assemblageA et assemblageb classe fonction de base

Eigen::VectorXd Equation::assembleb(const DiscreteSpace& discreteSpace) {
    // get dof and mesh.
    auto dof = discreteSpace.getDof();
    Eigen::VectorXd b = Eigen::VectorXd::Zero(dof->nIndexs());
    for (const auto& lf : linearForms) {
        lf->assemble(discreteSpace, b);
    }
    return b;
}

