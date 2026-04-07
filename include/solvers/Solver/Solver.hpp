#ifndef SOLVERS_LINEAR_SOLVER_HPP
#define SOLVERS_LINEAR_SOLVER_HPP

#include <Eigen/Sparse>
#include <Eigen/Dense>

class Solver {
public:
    virtual ~Solver() = default;

    /**
     * @brief Résout le système Ax = b
     * On utilise SparseMatrix car en FEM, les matrices sont creuses.
     */
    virtual Eigen::VectorXd solve(
        const Eigen::SparseMatrix<double>& A, 
        const Eigen::VectorXd& b) const = 0; // "= 0" rend la classe abstraite
};

#endif
