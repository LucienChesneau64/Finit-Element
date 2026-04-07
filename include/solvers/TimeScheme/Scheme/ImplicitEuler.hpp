#ifndef SOLVERS_TIME_SCHEME_SCHEME_IMPLICIT_EULER_HPP
#define SOLVERS_TIME_SCHEME_SCHEME_IMPLICIT_EULER_HPP

#include "solvers/TimeScheme/TimeScheme.hpp"

/**
 * @brief Schéma d'Euler Implicite (Ordre 1).
 * Résout le système (M + dt*K) U^{n+1} = M*U^n + dt*F
 */
template <size_t dim>
class ImplicitEuler : public TimeScheme<dim> {
public:
    // Utilise le constructeur de la classe de base (dt, solver)
    using TimeScheme<dim>::TimeScheme;

    /**
     * @brief Effectue un pas de temps en utilisant les matrices déjà assemblées.
     */
    void step(const Equation<dim>& eq, 
              const MultiField<dim>& mf, 
              GlobalAssembler<dim>& assembler, 
              const Eigen::SparseMatrix<double>& K,
              const Eigen::SparseMatrix<double>& M,
              State& currentState) override;
};

#endif

