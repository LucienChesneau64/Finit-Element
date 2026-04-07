#include "solvers/Simulation.hpp"
#include "physics/Operators/BilinearOperator/MassMatrix.hpp"
#include <iostream>

/**
 * @brief Boucle temporelle (Instationnaire)
 */

template <size_t dim>
void Simulation<dim>::run(double T_end) {
    std::cout << "--- Starting Unsteady Simulation ---" << std::endl;
    int size = multiField_->totalSize();
    Eigen::SparseMatrix<double> K(size, size);
    Eigen::SparseMatrix<double> M(size, size);

    // 1. Assemblage de la Rigidité (Physique de l'équation)
    assembler_.assembleStiffnessMatrix(K, *multiField_, *equation_);

    // 2. Assemblage de la Masse (Structurelle)
    // On crée l'opérateur de masse (ex: avec une densité de 1.0 par défaut)
    auto massOp = std::make_shared<MassOperator<dim>>(1.0); 
    assembler_.assembleMassMatrix(M, *multiField_, massOp);

    // 3. Sauvegarde de l'état initial (t=0)
    this->save();

    // 4. Boucle temporelle
    while (currentState_.time() < T_end) {
        // Le schéma de temps gère l'incrémentation du temps et de l'itération
        timeScheme_->step(*equation_, *multiField_, assembler_, K, M, currentState_);
        
        // Export des résultats
        this->save();
        
        std::cout << "Time: " << currentState_.time() << "s | Iteration: " 
                  << currentState_.iteration() << std::endl;
    }
    std::cout << "Simulation finished." << std::endl;
}

/**
 * @brief Résout le problème stationnaire A*u = b
 */
template <size_t dim>
void Simulation<dim>::solveSteadyState() {
    std::cout << "--- Solving Steady State ---" << std::endl;

    int totalSize = multiField_->totalSize();
    Eigen::SparseMatrix<double> A(totalSize, totalSize);
    Eigen::VectorXd b = Eigen::VectorXd::Zero(totalSize);

    // 1. Assemblage Global
    // Attention au nom : assembleVector et non assembleSourceVector
    assembler_.assembleStiffnessMatrix(A, *multiField_, *equation_);
    assembler_.assembleVector(b, *multiField_, *equation_);

    // 2. Conditions aux limites
    assembler_.applyBoundaryConditions(A, b, *multiField_, *equation_);

    // 3. Résolution
    std::cout << "Solving system of size " << totalSize << "..." << std::endl;
    
    // On récupère le solver interne
    Eigen::VectorXd result = timeScheme_->getSolver().solve(A, b);
    currentState_.setValues(result);

    // 4. Reset & Save
    currentState_.setTime(0.0);
    currentState_.setIteration(0);
    this->save();
    
    std::cout << "Steady state solved successfully." << std::endl;
}

/**
 * @brief Parcourt tous les writers enregistrés pour exporter les données
 */
template <size_t dim>
void Simulation<dim>::save() {
    for (auto& writer : writers_) {
        if (writer) {
            // On passe l'état (valeurs) et le multifield (maillage/mapping) au writer
            writer->write(currentState_, *multiField_);
        }
    }
}

// Instanciations explicites pour éviter les erreurs de lien au linkage
template class Simulation<2>;
template class Simulation<3>;