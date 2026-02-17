#include "Simulation.hpp"


// à ajouter TimeScheme.

Simulation::Simulation(std::shared_ptr<Equation> eq,
                       std::shared_ptr<Solver> sol,
                       std::shared_ptr<DiscreteSpace> discreteSpace_, 
                       std::vector<std::shared_ptr<ResultWriter>> writerList_)
    : equation(eq), solver(sol), discreteSpace(discreteSpace_), writerList(writerList_)  {}

void Simulation::run() {

    // loop on time. with while time < T, time += dt;

    auto A = equation->assembleStiffMatrix(discreteSpace);
    auto b = equation->assembleb(discreteSpace);
    // changer A et méthod assembleA en assembleStiffMatrix.
    

    Eigen::VectorXd x = solver->solve(A.toDense(), b);
    // modifier le .toDense si l'o veut qu ca reste sparse utiliser bonn méthode.

    // method pour écrire 
    for (auto& const writer: writerList) {
        writer->write(); // préciser les arguments du write.
        // devrait prndre en argument le temps, et la solution.
    }
}

