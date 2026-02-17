#include "Equation.hpp"


class TimeScheme {
    public:
        // destructor
        ~TimeScheme() = default;
        
        virtual void step(Equation equation, double dt);
};

// changer void en vecteur 