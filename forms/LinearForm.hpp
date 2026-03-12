#pragma once
#include <Eigen/Dense>
#include "DiscreteSpace.hpp"


template<size_t dim>
class LinearForm {
public:
    virtual ~LinearForm() = default;

    void assemble(const DiscreteSpace<dim>& discreteSpace,
                  Eigen::VectorXd& b) const;

    virtual double localContribution(const DiscreteSpace<dim>& discreteSpace, const Element<dim>& e,
                                     int local_i) const = 0;
};


