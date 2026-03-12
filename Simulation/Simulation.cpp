#include "Simulation.hpp"
#include "DofHandler.hpp"


Simulation::Simulation(
    State currentState_;
    std::shared_ptr<Equation> eq;
    std::shared_ptr<MultiField<dim>> multiField_);
        std::unique_ptr<TimeScheme> timeScheme_;
    : currentState(currentState_), equation(eq), multiField(multiField_), timeScheme(timeScheme_) {}

// demander ce qui est le plus propre, a mettre en membre privé ou en argument d'une methode?

void Simulation::run(const double T, const ResultWriter& resultWriter) {
    // T en argument + state pour condition initiale
    // loop on time. with while time < T, time += dt;
    // use of DofHandler to distribute

    auto A = equation->assembleStiffMatrix();
    auto b = equation->assembleb();
    // changer A et méthod assembleA en assembleStiffMatrix.
    

    //Eigen::VectorXd x = solver->solve(A.toDense(), b);
    // modifier le .toDense si l'o veut qu ca reste sparse utiliser bonn méthode.

    // method pour écrire 
    // réfléchir a la facon dont ca va se faire. coder classe State avant.
    for (auto& const writer: writerList) {
        writer->write(); // préciser les arguments du write.
        // devrait prndre en argument le temps, et la solution.
    }
}

void Simulation::stable()

// change of discretspace to multifield. 
// a list of or a struct in fact of different DiscreteSpace.
// on it, method globalDofhandler to assign all dof of every nodes.
// then globalDofhandler in assembleGlobalstiffMatrix(field, dof) ?
// revoir structur architecture AssembleMatrix.

// revoir run. 