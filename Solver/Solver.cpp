#pragma once
#include "Solver.hpp"

class IterativeSolver : public Solver {
protected:
    double tolerance;

public:
    explicit IterativeSolver(double tol);

    virtual Eigen::VectorXd step(const Eigen::MatrixXd& A,
                                 const Eigen::VectorXd& b,
                                 const Eigen::VectorXd& x) = 0;

    Eigen::VectorXd solve(const Eigen::MatrixXd& A,
                          const Eigen::VectorXd& b) override;
};

