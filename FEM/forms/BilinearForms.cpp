#include "BilinearForm.hpp"

void BilinearForm::assemble(const Mesh& mesh,
                            const DofHandler& dof,
                            Eigen::SparseMatrix<double>& A) const {
    for (const auto& elem : mesh.getElements()) {
        const auto& ids = elem.getNodeIds();

        for (int a = 0; a < 3; ++a) {
            int i = dof.dof(ids[a]);
            for (int b = 0; b < 3; ++b) {
                int j = dof.dof(ids[b]);
                A.coeffRef(i,j) += localContribution(elem, a, b);
            }
        }
    }
}


