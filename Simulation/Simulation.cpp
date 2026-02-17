#include "Simulation.hpp"


// à ajouter TimeScheme.

Simulation::Simulation(std::shared_ptr<Equation> eq,
                       std::shared_ptr<Solver> sol,
                       std::shared_ptr<DiscreteSpace> discreteSpace_, 
                       std::vector<std::shared_ptr<ResultWriter>> writerList_)
    : equation(eq), solver(sol), discreteSpace(discreteSpace_), writerList(writerList_)  {}

void Simulation::run() {

    // loop on time. with while time < T, time += dt;

    auto A = equation->assembleA(discreteSpace);
    auto b = equation->assembleb(discreteSpace);
    // changer A et méthod assembleA en assembleStiffMatrix.
    // construction mass matrix for step.
    // appel de step(StiffMatrix, b, MassMatrix) pour result.
    // a voir... comment agencer ca.

    Eigen::VectorXd x = solver->solve(A.toDense(), b);
    // modifire le .toDense().

    // method pour écrire 
    for (auto& const writer: writerList) {
        writer->write(); // préciser les arguments du write.
    }
}

