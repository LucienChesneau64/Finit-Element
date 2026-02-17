#pragma once
#include <Eigen/Dense>
#include "DiscreteSpace.hpp"

class LinearForm {
public:
    virtual ~LinearForm() = default;

    void assemble(const DiscreteSpace& discreteSpace,
                  Eigen::VectorXd& b) const;

    virtual double localContribution(const DiscreteSpace& discreteSpace, const Element& e,
                                     int local_i) const = 0;
};


