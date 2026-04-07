#ifndef PHYSICS_EQUATION_HPP
#define PHYSICS_EQUATION_HPP

#include <vector>
#include <memory>

// Inclusions basées sur ton arborescence
#include "physics/Operators/BilinearOperator/IBilinearOperator.hpp"
#include "physics/Operators/LinearOperator/ILinearOperator.hpp"
#include "physics/Operators/BoundedCondition/BoundaryCondition.hpp"

/**
 * @brief Structures de stockage pour les termes de l'EDP
 */
template <size_t dim>
struct BilinearTerm {
    std::shared_ptr<IBilinearOperator<dim>> op;
    int testFieldId;
    int trialFieldId;
};

template <size_t dim>
struct LinearTerm {
    std::shared_ptr<ILinearOperator<dim>> op;
    int testFieldId;
};

/**
 * @brief La classe Equation définit le système d'EDP à résoudre.
 * Elle stocke les opérateurs bilinéaires (Matrice), linéaires (Vecteur) et les CL.
 */
template <size_t dim>
class Equation {
private:
    std::vector<BilinearTerm<dim>> bilinearTerms_;
    std::vector<LinearTerm<dim>> linearTerms_;
    std::vector<std::shared_ptr<BoundaryCondition<dim>>> boundaryConditions_;

public:
    Equation() = default;

    /**
     * @brief Ajoute un terme bilinéaire (ex: intégrale de grad(u).grad(v))
     */
    void addBilinearTerm(std::shared_ptr<IBilinearOperator<dim>> op, int testId, int trialId) {
        bilinearTerms_.push_back({op, testId, trialId});
    }

    /**
     * @brief Ajoute un terme linéaire (ex: intégrale de f.v)
     */
    void addLinearTerm(std::shared_ptr<ILinearOperator<dim>> op, int testId) {
        linearTerms_.push_back({op, testId});
    }

    /**
     * @brief Ajoute une condition aux limites (Dirichlet, Neumann...)
     */
    void addBoundaryCondition(std::shared_ptr<BoundaryCondition<dim>> bc) {
        boundaryConditions_.push_back(bc);
    }

    // --- Getters pour le GlobalAssembler ---
    const std::vector<BilinearTerm<dim>>& getBilinearTerms() const { return bilinearTerms_; }
    const std::vector<LinearTerm<dim>>& getLinearTerms() const { return linearTerms_; }
    const std::vector<std::shared_ptr<BoundaryCondition<dim>>>& getBoundaryConditions() const { return boundaryConditions_; }

    void clear() {
        bilinearTerms_.clear();
        linearTerms_.clear();
        boundaryConditions_.clear();
    }
};

#endif