#pragma once
#include <Eigen/Sparse>
#include "DiscreteSpace.hpp"


template<siz_t dim>

class BilinearForm {
public:
    virtual ~BilinearForm() = default;

    void assemble(const DiscreteSpace<dim>&,
                  Eigen::SparseMatrix<double>& A) const;

    virtual double localContribution(const DiscreteSpace<dim>& discreteSpace, const Element<dim>& e,
                                     int local_i,
                                     int local_j) const = 0;
};


