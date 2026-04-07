#ifndef SOLVERS_SIMULATION_HPP
#define SOLVERS_SIMULATION_HPP

#include <memory>
#include <vector>

#include "solvers/State.hpp"
#include "core/Space/MultiField.hpp"
#include "physics/Equation.hpp"
#include "physics/GlobalAssembler.hpp"
#include "solvers/TimeScheme/TimeScheme.hpp"
#include "io/ResultWriter.hpp"

template <size_t dim>
class Simulation {
private:
    State currentState_;
    std::shared_ptr<Equation<dim>> equation_;
    std::shared_ptr<MultiField<dim>> multiField_;
    
    // Moteurs
    std::unique_ptr<TimeScheme<dim>> timeScheme_;
    GlobalAssembler<dim> assembler_;

    // Liste des exporteurs (VTK, CSV, HDF5...)
    std::vector<std::shared_ptr<ResultWriter<dim>>> writers_;

public:
    /**
     * @brief Constructeur de la simulation.
     */
    Simulation(
        const State& initialState,
        std::shared_ptr<Equation<dim>> eq,
        std::shared_ptr<MultiField<dim>> mf,
        std::unique_ptr<TimeScheme<dim>> scheme
    ) : currentState_(initialState), 
        equation_(eq), 
        multiField_(mf), 
        timeScheme_(std::move(scheme)) {}

    ~Simulation() = default;

    /**
     * @brief Ajoute un moteur d'export (ex: VTKWriter).
     */
    void addWriter(std::shared_ptr<ResultWriter<dim>> writer) {
        writers_.push_back(writer);
    }

    /**
     * @brief Boucle temporelle de t_start à T_end.
     */
    void run(double T_end);

    /**
     * @brief Résout le problème statique A*u = b.
     */
    void solveSteadyState();

    /**
     * @brief Parcourt tous les writers pour sauvegarder l'état actuel.
     */
    void save();

    // --- Getters ---
    const State& getState() const { return currentState_; }
    double getCurrentTime() const { return currentState_.time(); }
};

#endif