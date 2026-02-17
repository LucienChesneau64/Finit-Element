#include "LinearForm.hpp"

void LinearForm::assemble(const DiscreteSpace& discreteSpace,
                          Eigen::VectorXd& b) const {
    auto& mesh = discreteSpace.getMesh();
    auto& dof = discreteSpace.getDof();
    auto& basisFunction = discreteSpace.getBasisFunction();
    for (const auto& elem : mesh->getElements()) {
        const auto& ids = elem.getNodeIds();

        for (int a = 0; a < 3; ++a) {
            int i = dof->Index(ids[a]);
            b(i) += localContribution(discreteSpace, elem, a);
        }
    }
}



// int nLocalDofs = basisFunction->nLocalDofs(elem);
//for (int a = 0; a < nLocalDofs; ++a)
// pour P1 - Pn

