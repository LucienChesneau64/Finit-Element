#pragma once
#include <memory>
#include "Equation.hpp"
#include "Solver.hpp"

class Simulation {
private:
    std::shared_ptr<Equation> equation;
    std::shared_ptr<Solver> solver;

public:
    Simulation(std::shared_ptr<Equation> eq,
               std::shared_ptr<Solver> sol);

    void run();
};


