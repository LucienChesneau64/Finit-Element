#pragma once
#include <Eigen/Sparse>
#include "DiscreteSpace.hpp"

class BilinearForm {
public:
    virtual ~BilinearForm() = default;

    void assemble(const DiscreteSpace&,
                  Eigen::SparseMatrix<double>& A) const;

    virtual double localContribution(const DiscreteSpace& discreteSpace, const Element& e,
                                     int local_i,
                                     int local_j) const = 0;
};

// créer la classe DiscreteSpace qui représente Vh.
// au lieu de prendre en entrée Mesh, indexHandler, et BasisFunction -> DiscreteSpace.

