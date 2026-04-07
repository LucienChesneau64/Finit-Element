#include <iostream>
#include <memory>
#include <Eigen/Dense>

// --- CORE & SPACE ---
#include "core/Geometry/Mesh.hpp"
#include "core/Space/DiscreteSpace.hpp"
#include "core/Space/MultiField.hpp"
#include "solvers/State.hpp"
#include "core/FE/basisfunction/P1.hpp" // Inclus pour instancier P1

// --- PHYSICS & OPERATORS ---
#include "physics/Equation.hpp"
#include "physics/Operators/BilinearOperator/LaplaceOperator.hpp"
#include "physics/Operators/LinearOperator/SourceTermOperator.hpp"
#include "physics/Operators/BoundedCondition/DirichletConditions.hpp"

// --- SOLVERS ---
#include "solvers/Solver/LUSolver.hpp"

// --- TIME SCHEMES & SIMULATION ---
#include "solvers/TimeScheme/Scheme/ImplicitEuler.hpp"
#include "solvers/Simulation.hpp" 

// --- IO ---
#include "io/VTKWriter.hpp"

int main() {
    try {
        std::cout << "--- Initializing FEM Simulation (v2.0 Clean) ---" << std::endl;
        

        // 1. MAILLAGE : Carré unité 2D
        auto mesh = std::make_shared<Mesh<2>>();
        std::cout << "Loading mesh..." << std::endl;
        mesh->loadFromFile("square.msh"); 
        std::cout << "Mesh loaded: " << mesh->getNNodes() << " nodes." << std::endl;

        // 2. ESPACES DISCRETS : Température en P1
        auto p1Shape = std::make_shared<P1<2>>(); 
        auto tempSpace = std::make_shared<DiscreteSpace<2>>(mesh, p1Shape);

        // 3. MULTIFIELD : Gestion des DDL globaux
        auto mf = std::make_shared<MultiField<2>>();
        int tempId = mf->addField("Temperature", tempSpace);
        mf->updateDofs(); 

        // 4. ÉQUATION : Physique du problème (-Delta T = f)
        auto equation = std::make_shared<Equation<2>>();
        
        // --- Terme de Diffusion (Laplacien) ---
        auto laplace = std::make_shared<LaplaceOperator<2>>(1.0); 
        equation->addBilinearTerm(laplace, tempId, tempId);

        // --- Terme Source (f) ---
        
        auto source = std::make_shared<SourceTermOperator<2>>([](const Eigen::Vector2d& x) {
            double dist = (x - Eigen::Vector2d(0.5, 0.5)).norm();
            return (dist < 0.2) ? 100.0 : 0.0; 
        });

        
        /*auto source = std::make_shared<SourceTermOperator<2>>([](const Eigen::Vector2d& x) {
        return 10.0; // Énorme chaleur partout
        });
        */
        equation->addLinearTerm(source, tempId);

        // --- Conditions aux limites ---
        auto bc = std::make_shared<DirichletConditions<2>>(tempId, 101, 0.0);
        equation->addBoundaryCondition(bc);

        // 5. SOLVEUR LINÉAIRE
        auto mySolver = std::make_shared<LUSolver>(); 

        // 6. SCHÉMA DE TEMPS (Euler Implicite)
        double dt = 0.05;
        auto scheme = std::make_unique<ImplicitEuler<2>>(dt, mySolver);

        // 7. ÉTAT INITIAL (Vecteur de taille Dofs totaux)
        State initialState(mf->totalSize());
        initialState.setTime(0.0);
        initialState.setIteration(0);

        // 8. SIMULATION
        Simulation<2> sim(initialState, equation, mf, std::move(scheme));

        //  writer VTK
        auto vtkWriter = std::make_shared<VTKWriter<2>>("results/sim_output");
        sim.addWriter(vtkWriter);

        // 9. EXÉCUTION
        std::cout << "Starting Transient Simulation (dt = " << dt << "s)..." << std::endl;
        sim.run(2.0); 
        //sim.solveSteadyState();

        std::cout << "--- Simulation Finished Successfully ---" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "CRITICAL ERROR: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

