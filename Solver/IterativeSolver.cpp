#include "IterativeSolver.hpp"

IterativeSolver::IterativeSolver(double tol)
    : tolerance(tol) {}

Eigen::VectorXd IterativeSolver::solve(const Eigen::MatrixXd& A,
                                       const Eigen::VectorXd& b) {
    Eigen::VectorXd x = Eigen::VectorXd::Zero(b.size());

    while ((A*x - b).norm() > tolerance) {
        x = step(A, b, x);
    }
    return x;
}

