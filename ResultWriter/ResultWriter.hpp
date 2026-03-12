#include <iostream>
#include <Eigen/Dense>
#include "DiscreteSpace.hpp"
// #include HTF5 en binaire

class ResultWriter
{
    // destructor
    ~ResultWriter() = default;

    virtual void write(
        const Mesh &mesh,
        const IndexHandler &dof,
        const Eigen::VectorXd &solution,
        double time = 0) = 0;
};

// au lieu de mesh. MultiField, GlobalDofHandler, vecteur x (ou State à la place de GlobalDofHandler et vecteur x. a voir.) et time.