#include "physics/Operators/BoundedCondition/DirichletConditions.hpp"

template <size_t dim>
void DirichletConditions<dim>::apply(
    Eigen::SparseMatrix<double>& A, 
    Eigen::VectorXd& b, 
    const MultiField<dim>& mf) const 
{
    const auto& space = mf.getSpace(this->fieldId_);
    const auto& mesh = space->mesh();
    
    // Utilise NbFields() ou nbFields() selon ton MultiField.hpp
    int fieldOffset = mf.getFieldOffset(this->fieldId_);

    // 1. On récupère les nœuds du bord
    auto boundaryNodes = mesh.getNodesOnBoundary(this->boundaryId_);

    // 2. On boucle directement sur ces nœuds
    for (int nodeId : boundaryNodes) {
        
        // Calcul de l'indice global du DDL
        // Si P1 : 1 noeud = 1 DDL
        int globalIdx = fieldOffset + nodeId; 

        // 3. Imposer la condition dans b
        b(globalIdx) = this->value_;

        // 4. Diagonalisation de la matrice A
        // On met à 0 toute la ligne, et 1 sur la diagonale
        for (int k = 0; k < A.outerSize(); ++k) {
            for (Eigen::SparseMatrix<double>::InnerIterator it(A, k); it; ++it) {
                if (it.row() == globalIdx) {
                    it.valueRef() = (it.col() == globalIdx) ? 1.0 : 0.0;
                }
            }
        }
    }
}

template class DirichletConditions<2>;
template class DirichletConditions<3>;