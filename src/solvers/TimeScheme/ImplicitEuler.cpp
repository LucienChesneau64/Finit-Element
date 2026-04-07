#include "solvers/TimeScheme/Scheme/ImplicitEuler.hpp"
#include <iostream>

template <size_t dim>
void ImplicitEuler<dim>::step(const Equation<dim>& eq, 
                      const MultiField<dim>& mf, 
                      GlobalAssembler<dim>& assembler, 
                      const Eigen::SparseMatrix<double>& K,
                      const Eigen::SparseMatrix<double>& M,
                      State& currentState)
{
    // --- 1. Préparation des variables ---
    int totalSize = mf.totalSize();
    double dt = this->dt_;
    
    // Solution au pas de temps actuel (u_n)
    Eigen::VectorXd Un = currentState.getValues();

    // --- 2. Assemblage des sources ---
    Eigen::VectorXd F = Eigen::VectorXd::Zero(totalSize);
    assembler.assembleVector(F, mf, eq);

    // --- 3. Construction du système linéaire A * u_{n+1} = b ---
    
    Eigen::SparseMatrix<double> A(totalSize, totalSize);
    Eigen::VectorXd b(totalSize);

    // TODO: [À COMPLÉTER] Formule pour A (ex: M/dt + K)
    A = M + dt*K;
    
    // TODO: [À COMPLÉTER] Formule pour b (ex: M/dt * Un + F)
    b = M*Un + dt*F;

    // --- 4. Conditions aux Limites ---
    assembler.applyBoundaryConditions(A, b, mf, eq);

    // --- 5. Résolution ---
    std::cout << "Solving iteration " << currentState.iteration() + 1 << "..." << std::endl;
    Eigen::VectorXd nextValues = this->solver_->solve(A, b);
    
    // --- 6. Mise à jour de l'état ---
    currentState.setValues(nextValues);
    currentState.setTime(currentState.time() + dt);
    currentState.setIteration(currentState.iteration() + 1);
}

// --- Instanciations explicites ---
template class ImplicitEuler<2>;
template class ImplicitEuler<3>;

