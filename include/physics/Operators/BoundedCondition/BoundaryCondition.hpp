#ifndef PHYSICS_OPERATORS_BOUNDED_CONDITION_BOUNDARY_CONDITION_HPP
#define PHYSICS_OPERATORS_BOUNDED_CONDITION_BOUNDARY_CONDITION_HPP

#include <Eigen/Sparse>
#include "core/Space/MultiField.hpp"

/**
 * @brief Classe de base abstraite pour les conditions aux limites (Dirichlet, Neumann, etc.).
 */
template <size_t dim>
class BoundaryCondition {
protected:
    int fieldId_;      // Index du champ dans le MultiField (ex: 0 pour T)
    int boundaryId_;   // ID physique défini dans GMSH (ex: 101 pour "Bord Gauche")

public:
    BoundaryCondition(int fieldId, int boundaryId) 
        : fieldId_(fieldId), boundaryId_(boundaryId) {}
    
    virtual ~BoundaryCondition() = default;

    /**
     * @brief Modifie la matrice A et le vecteur b pour imposer la condition.
     * Appelé par le GlobalAssembler APRÈS l'assemblage volumique.
     */
    virtual void apply(Eigen::SparseMatrix<double>& A, 
                       Eigen::VectorXd& b, 
                       const MultiField<dim>& mf) const = 0;
};

#endif

