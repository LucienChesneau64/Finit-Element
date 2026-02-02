#include "Simulation.hpp"

Simulation::Simulation(std::shared_ptr<Equation> eq,
                       std::shared_ptr<Solver> sol)
    : equation(eq), solver(sol) {}

void Simulation::run() {
    auto A = equation->assembleA();
    auto b = equation->assembleb();

    Eigen::VectorXd x = solver->solve(A.toDense(), b);
}

