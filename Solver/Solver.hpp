#pragma once
#include <Eigen/Dense>

class Solver {
public:
    virtual ~Solver() = default;
    virtual Eigen::VectorXd solve(const Eigen::MatrixXd& A,
                                  const Eigen::VectorXd& b) = 0;
};

