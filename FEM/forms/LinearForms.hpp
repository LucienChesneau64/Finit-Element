#pragma once
#include <Eigen/Dense>
#include "Mesh.hpp"
#include "DofHandler.hpp"

class LinearForm {
public:
    virtual ~LinearForm() = default;

    void assemble(const Mesh& mesh,
                  const DofHandler& dof,
                  Eigen::VectorXd& b) const;

    virtual double localContribution(const Element& e,
                                     int local_i) const = 0;
};


