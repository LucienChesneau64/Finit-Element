#include "TimeScheme.hpp"
#include "Solver.hpp"

class Euler : public TimeScheme {
    private:
        std::unique_ptr<Solver>;
    public:
        // constructeur

        // destructeur

        void step(Equation equation ,double dt) override; 
};

// ajout des conditions initiales. ou ???