#include "Equation.hpp"
#include "MultiField.hpp"
#include "State.hpp"


class TimeScheme {
    private:
        double dt;
    public:
        ~TimeScheme() = default;
        
        virtual void step(const Equation& equation, const MultiField& multifield, State& currentState) = 0;

        double getDt();
};

