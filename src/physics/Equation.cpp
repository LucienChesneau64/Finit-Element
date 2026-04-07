#include "physics/Equation.hpp"

// On ne réécrit AUCUNE méthode ici (elles sont déjà dans le .hpp)
// On se contente de dire au compilateur de préparer les versions 2D et 3D.

template class Equation<2>;
template class Equation<3>;