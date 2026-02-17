#include <iostream>
#include <Eigen/Dense>
#include "DiscreteSpace.hpp"
// #include HTF5 en binaire


class ResultWriter {
    // destructor
    ~ResultWriter() = default;

    virtual void write(
        const Mesh& mesh,
        const IndexHandler& dof,
        const Eigen::VectorXd& solution,
        double time = 0
    ) = 0;
};

