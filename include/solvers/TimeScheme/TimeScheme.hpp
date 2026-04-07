#ifndef SOLVERS_TIME_SCHEME_TIME_SCHEME_HPP
#define SOLVERS_TIME_SCHEME_TIME_SCHEME_HPP

#include <memory>
#include <Eigen/Sparse> // Nécessaire pour SparseMatrix

#include "physics/Equation.hpp"
#include "core/Space/MultiField.hpp"
#include "solvers/State.hpp"
#include "physics/GlobalAssembler.hpp"
#include "solvers/Solver/Solver.hpp" 

template <size_t dim>
class TimeScheme {
protected:
    double dt_;
    std::shared_ptr<Solver> solver_;

public:
    TimeScheme(double dt, std::shared_ptr<Solver> solver) 
        : dt_(dt), solver_(solver) {}
        
    virtual ~TimeScheme() = default;

    /**
     * @brief Effectue un pas de temps.
     * @param K Matrice de rigidité (Stiffness) déjà assemblée.
     * @param M Matrice de masse (Mass) déjà assemblée.
     */
    virtual void step(const Equation<dim>& eq, 
                      const MultiField<dim>& mf, 
                      GlobalAssembler<dim>& assembler, 
                      const Eigen::SparseMatrix<double>& K,
                      const Eigen::SparseMatrix<double>& M,
                      State& currentState) = 0;

    double getDt() const { return dt_; }
    void setDt(double dt) { dt_ = dt; }
    
    Solver& getSolver() { return *solver_; }
};

#endif