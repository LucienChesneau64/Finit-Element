#include "Equation.hpp"

Equation::Equation(const Mesh& mesh_)
    : mesh(mesh_) {
    dof.distributeDofs(mesh);
}

Eigen::SparseMatrix<double> Equation::assembleA() {
    Eigen::SparseMatrix<double> A(dof.nDofs(), dof.nDofs());
    for (const auto& bf : bilinearForms) {
        bf->assemble(mesh, dof, A);
    }
    return A;
}

Eigen::VectorXd Equation::assembleb() {
    Eigen::VectorXd b = Eigen::VectorXd::Zero(dof.nDofs());
    for (const auto& lf : linearForms) {
        lf->assemble(mesh, dof, b);
    }
    return b;
}

