#include "solvers/Solver/Solver.hpp"
#include <Eigen/IterativeLinearSolvers>

class CGSolver : public Solver {
private:
    double tol_;
public:
    explicit CGSolver(double tol = 1e-9) : tol_(tol) {}

    Eigen::VectorXd solve(const Eigen::SparseMatrix<double>& A, 
                          const Eigen::VectorXd& b) const override 
    {
        Eigen::ConjugateGradient<Eigen::SparseMatrix<double>> cg;
        cg.setTolerance(tol_);
        cg.compute(A);
        return cg.solve(b);
    }
};