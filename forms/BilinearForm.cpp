#include "BilinearForm.hpp"

void BilinearForm::assemble(const DiscreteSpace& discreteSpace,
                            Eigen::SparseMatrix<double>& A) const {

    // getMesh, getDof, getBasisFunction
    
    auto mesh = discreteSpace.getMesh();
    auto index = discreteSpace.getDof();
    auto basisFunction = discreteSpace.getBasisFunction();

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


//int nLocalDofs = basisFunction->nLocalDofs(elem);
//for (int a = 0; a < nLocalDofs; ++a)

// changer pour logique P1 - Pn
