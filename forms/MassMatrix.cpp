#include "MassMatrix.hpp"


double MassMatrix::localContribution(
    const DiscreteSpace<dim>& discreteSpace, 
    const Element<dim>& e, 
    int local_i, int local_j) {

        // coder la contribution local... -> integral sur element de phi_i * phi_j . avec phi fonctions de bases.
        return contribution;
    }
