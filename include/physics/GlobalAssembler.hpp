#ifndef PHYSICS_GLOBAL_ASSEMBLER_HPP
#define PHYSICS_GLOBAL_ASSEMBLER_HPP

#include <Eigen/Sparse>
#include <vector>
#include <memory>
#include "core/Space/MultiField.hpp"
#include "physics/Equation.hpp"

template <size_t dim>
class GlobalAssembler {
public:
    GlobalAssembler() = default;

    // Prend l'équation pour boucler sur tous les termes sources (LinearTerms)
    void assembleVector(Eigen::VectorXd& F, 
                        const MultiField<dim>& mf, 
                        const Equation<dim>& eq); 

    void applyBoundaryConditions(Eigen::SparseMatrix<double>& A, 
                                 Eigen::VectorXd& b, 
                                 const MultiField<dim>& mf, 
                                 const Equation<dim>& eq);
    
    // Prend un opérateur spécifique pour la masse (ta volonté de découplage)
    void assembleMassMatrix(Eigen::SparseMatrix<double>& M, 
                            const MultiField<dim>& mf, 
                            std::shared_ptr<IBilinearOperator<dim>> massOp);

    // Prend l'équation pour boucler sur la physique (BilinearTerms)
    void assembleStiffnessMatrix(Eigen::SparseMatrix<double>& K, 
                                 const MultiField<dim>& mf, 
                                 const Equation<dim>& eq);

private:
    void collectTriplets(std::vector<Eigen::Triplet<double>>& triplets, 
                         const MultiField<dim>& mf, 
                         const BilinearTerm<dim>& term);

    void addLocalToTriplets(std::vector<Eigen::Triplet<double>>& triplets,
                           const Eigen::MatrixXd& localMat,
                           const std::vector<int>& rowIndices,
                           const std::vector<int>& colIndices);
};

#endif

