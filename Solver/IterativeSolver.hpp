#pragma once
#include "Solver.hpp"


class IterativeSolver: public Solver {
	private:
		double error;
	public:
		// constructeur
		IterativeSolver(double error_): Solver(), error(error_) {};
		// destructeur
		~IterativeSolver() = default; 
		// minimize methods -> mieux appeler // gérer rhs, et vecteur x.
		virtual Eigen::VectorXd step(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x ) = 0; // methode interface
		Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);
};