#pragma once
#include <memory>
#include <vector>
#include "Equation.hpp"
#include "Solver.hpp"
#include "MultiField.hpp"
#include "State.hpp"

template <size_t dim>
class Simulation
{
private:
    State currentState;
    State nextState;
    std::shared_ptr<Equation> equation;
    std::shared_ptr<MultiField<dim>> MultiField;
    std::unique_ptr<TimeScheme> timeScheme;

public:
    Simulation(
        State currentState;
        std::shared_ptr<Equation> eq,
        std::shared_ptr<MultiField<dim>> multiField_,
        std::unique_ptr<TimeScheme> timeScheme,

                       writerList_); // 

    // destructeur
    ~Simulation() = default;

    void run(double T_end, std::vector<std::shared_ptr<ResultWriter>> writerList);
    // choix des paramètres TimeScheme.
    // scheme en choix aussi. scheme qui prend en argument lors de sa construction un solver. 


    void stable();
    // du/dt = 0.
    // prend en argument un solver.
};


// refactoring intégrale de cette fonction, pour ajout multifield, globalDofHandler.

// repenser quoi mettre en membre privé. 

// parce que on pourrait mettre InitialCondition dans Equation.
// on pourrait mettre writerList en membre privé.

// pour moi run() devrait prendre plutot en argument temps T.
// time scheme devrait prendre en membre privé pas de temps dt. ??? -> moi je dirai que oui.
// demander a gemini :))))).
