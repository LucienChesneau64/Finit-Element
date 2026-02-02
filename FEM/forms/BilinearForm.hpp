#pragma once
#include <Eigen/Sparse>
#include "Mesh.hpp"
#include "DofHandler.hpp"

class BilinearForm {
public:
    virtual ~BilinearForm() = default;

    void assemble(const Mesh& mesh,
                  const DofHandler& dof,
                  Eigen::SparseMatrix<double>& A) const;

    virtual double localContribution(const Element& e,
                                     int local_i,
                                     int local_j) const = 0;
};


