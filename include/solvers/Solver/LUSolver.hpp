#ifndef SOLVERS_LINEAR_DIRECT_LUSOLVER_HPP
#define SOLVERS_LINEAR_DIRECT_LUSOLVER_HPP

#include <Eigen/Sparse>
#include <Eigen/SparseLU>
#include "solvers/Solver/Solver.hpp" // Assure-toi que le chemin est correct

/**
 * @brief Solveur direct utilisant la décomposition LU d'Eigen (SparseLU).
 * Très robuste pour les systèmes de taille moyenne en 2D/3D.
 */
class LUSolver : public Solver {
public:
    LUSolver() = default;
    virtual ~LUSolver() = default;

    /**
     * @brief Résout le système Ax = b
     * @param A Matrice creuse (Stiffness + Mass + BCs)
     * @param b Vecteur second membre
     * @return Eigen::VectorXd La solution x
     */
    Eigen::VectorXd solve(const Eigen::SparseMatrix<double>& A, 
                          const Eigen::VectorXd& b) const override 
    {
        // On utilise la factorisation LU pour matrices creuses d'Eigen
        Eigen::SparseLU<Eigen::SparseMatrix<double>> solver;

        // 1. Analyse de la structure de la matrice
        solver.analyzePattern(A);
        
        // 2. Factorisation numérique
        solver.factorize(A);

        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("LUSolver: Factorization failed. Matrix might be singular.");
        }

        // 3. Résolution
        Eigen::VectorXd x = solver.solve(b);

        if (solver.info() != Eigen::Success) {
            throw std::runtime_error("LUSolver: Solving failed.");
        }

        return x;
    }
};

#endif