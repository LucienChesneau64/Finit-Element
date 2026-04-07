#include "physics/GlobalAssembler.hpp"


template <size_t dim>
void GlobalAssembler<dim>::collectTriplets(
    std::vector<Eigen::Triplet<double>>& triplets,
    const MultiField<dim>& mf, 
    const BilinearTerm<dim>& term)
{
    int targetType = (dim == 2) ? 2 : 4;
    auto spaceTest = mf.getSpace(term.testFieldId);
    auto spaceTrial = mf.getSpace(term.trialFieldId);
    
    int rowOffset = mf.getFieldOffset(term.testFieldId);
    int colOffset = mf.getFieldOffset(term.trialFieldId);

    for (const auto& el : spaceTest->mesh().getElements()) {
        if (el.getType() != targetType) continue;

        Eigen::MatrixXd Ak = term.op->computeLocalMatrix(el, *spaceTest, *spaceTrial);
        auto rowIndices = spaceTest->getMapper().getLocalIndices(el);
        auto colIndices = spaceTrial->getMapper().getLocalIndices(el);

        for(int& r : rowIndices) r += rowOffset;
        for(int& c : colIndices) c += colOffset;

        addLocalToTriplets(triplets, Ak, rowIndices, colIndices);
    }
}


// --- ASSEMBLAGE VECTEUR (Source / Force) ---
template <size_t dim>
void GlobalAssembler<dim>::assembleVector(
    Eigen::VectorXd& F, 
    const MultiField<dim>& mf, 
    const Equation<dim>& eq) 
{
    F.setZero(mf.totalSize()); // On initialise à zéro au début
    
    for (const auto& term : eq.getLinearTerms()) {
        auto space = mf.getSpace(term.testFieldId);
        int offset = mf.getFieldOffset(term.testFieldId);
        int targetType = (dim == 2) ? 2 : 4;

        for (const auto& el : space->mesh().getElements()) {
            if (el.getType() != targetType) continue;

            Eigen::VectorXd Fk = term.op->computeLocalVector(el, *space);
            auto indices = space->getMapper().getLocalIndices(el);

            for (int i = 0; i < (int)indices.size(); ++i) {
                F(indices[i] + offset) += Fk(i);
            }
        }
    }
}

// --- APPLICATION DES CONDITIONS AUX LIMITES ---
template <size_t dim>
void GlobalAssembler<dim>::applyBoundaryConditions(
    Eigen::SparseMatrix<double>& A, 
    Eigen::VectorXd& b, 
    const MultiField<dim>& mf, 
    const Equation<dim>& eq) 
{
    // On boucle sur toutes les CL définies (Dirichlet, etc.)
    for (const auto& bc : eq.getBoundaryConditions()) {
        bc->apply(A, b, mf);
    }
    A.makeCompressed();
}


template <size_t dim>
void GlobalAssembler<dim>::assembleStiffnessMatrix(
    Eigen::SparseMatrix<double>& K, 
    const MultiField<dim>& mf, 
    const Equation<dim>& eq) 
{
    std::vector<Eigen::Triplet<double>> triplets;
    // On réserve de la place pour la performance (environ 30 non-zéros par ligne en P1)
    triplets.reserve(mf.totalSize() * 30); 

    K.resize(mf.totalSize(), mf.totalSize());

    for (const auto& term : eq.getBilinearTerms()) {
        this->collectTriplets(triplets, mf, term); 
    }

    K.setFromTriplets(triplets.begin(), triplets.end());
    K.makeCompressed();
}

template <size_t dim>
void GlobalAssembler<dim>::assembleMassMatrix(
    Eigen::SparseMatrix<double>& M, 
    const MultiField<dim>& mf,
    std::shared_ptr<IBilinearOperator<dim>> massOp) 
{
    // 1. Initialisation
    std::vector<Eigen::Triplet<double>> triplets;
    // On réserve de la place : environ 10 à 15 non-zéros par ligne pour de la masse en P1
    triplets.reserve(mf.totalSize() * 15); 
    
    M.resize(mf.totalSize(), mf.totalSize());
    int targetType = (dim == 2) ? 2 : 4; // Triangle en 2D, Tétraèdre en 3D

    // 2. Boucle sur chaque champ du MultiField (ex: Champ 0 = T, Champ 1 = P)
    for (size_t fId = 0; fId < mf.NbFields(); ++fId) {
        auto space = mf.getSpace(fId);
        int offset = mf.getFieldOffset(fId);

        // 3. Boucle sur les éléments du maillage de cet espace
        for (const auto& el : space->mesh().getElements()) {
            // On ne traite que les éléments volumiques (pas les bords ici)
            if (el.getType() != targetType) continue;

            // 4. Calcul de la matrice de masse locale (Mk)
            // L'opérateur calcule \int (phi_i * phi_j) dV
            // On passe 'space' deux fois car c'est une forme bilinéaire symétrique (u, v)
            Eigen::MatrixXd Mk = massOp->computeLocalMatrix(el, *space, *space);
            
            // 5. Récupération des indices globaux via le Mapper
            auto indices = space->getMapper().getLocalIndices(el);
            
            // 6. Application de l'Offset du champ
            // Cela place le bloc de masse au bon endroit sur la diagonale du MultiField
            for(int& idx : indices) {
                idx += offset;
            }

            // 7. Transfert vers le vecteur de triplets (Scatter)
            // Comme c'est la matrice de masse d'un champ seul, 
            // les rowIndices et colIndices sont les mêmes.
            this->addLocalToTriplets(triplets, Mk, indices, indices);
        }
    }

    // 8. Finalisation de la matrice creuse
    // Eigen trie les triplets et additionne les doublons automatiquement
    M.setFromTriplets(triplets.begin(), triplets.end());
    M.makeCompressed();
}


template <size_t dim>
void GlobalAssembler<dim>::addLocalToTriplets(
    std::vector<Eigen::Triplet<double>>& triplets,
    const Eigen::MatrixXd& localMat,
    const std::vector<int>& rowIndices,
    const std::vector<int>& colIndices) 
{
    // On parcourt la matrice locale (ex: 3x3 pour un triangle P1)
    for (int i = 0; i < (int)rowIndices.size(); ++i) {
        for (int j = 0; j < (int)colIndices.size(); ++j) {
            // On crée un triplet (LigneGlobale, ColonneGlobale, Valeur)
            // Eigen gérera la somme si plusieurs triplets ont les mêmes coordonnées
            triplets.emplace_back(rowIndices[i], colIndices[j], localMat(i, j));
        }
    }
}

// Instanciations explicites
template class GlobalAssembler<2>;
template class GlobalAssembler<3>;