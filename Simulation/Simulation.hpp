#pragma once
#include <memory>
#include <vector>
#include "Equation.hpp"
#include "Solver.hpp"


// ajout de TimeScheme en argument;

class Simulation {
private:
    std::shared_ptr<Equation> equation;
    std::shared_ptr<Solver> solver;
    std::shared_ptr<DiscreteSpace> discreteSpace;
    std::vector<std::shared_ptr<ResultWriter>> writerList;
public:
    Simulation(std::shared_ptr<Equation> eq,
               std::shared_ptr<Solver> sol,
               std::shared_ptr<DiscreteSpace> discretespace_
               std::vector<std::shared_ptr<ResultWriter>> writerList_
            );

    // destructeur
    ~Simulation() = default;

    void run();
    // argument time, initConditions. à réfléchir. 


    // ajout méthode cas stable du/dt = 0.
};






