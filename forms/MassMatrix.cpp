#include "MassMatrix.hpp"


double MassMatrix::localContribution(
    const DiscreteSpace& discreteSpace, 
    const Element& e, 
    int local_i, int local_j) {

        // coder la contribution local... -> integral sur element de phi_i * phi_j . avec phi fonctions de bases.
        return contribution;
    }
