#include "LinearForm.hpp"

void LinearForm::assemble(const Mesh& mesh,
                          const DofHandler& dof,
                          Eigen::VectorXd& b) const {
    for (const auto& elem : mesh.getElements()) {
        const auto& ids = elem.getNodeIds();

        for (int a = 0; a < 3; ++a) {
            int i = dof.dof(ids[a]);
            b(i) += localContribution(elem, a);
        }
    }
}

