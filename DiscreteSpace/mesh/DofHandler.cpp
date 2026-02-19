#include "DofHandler.hpp"


void DofHandler::parseDofHandler(const Mesh<dim>& mesh, const Field field) {
    // on doit pour chaque noeuds attibruer des degrés de libertés.
    // va dépendre de la dimension et des fonctions de P1-PN et state?
    // doit prendre en entrée le mesh, mais aussi BasisFunction.?  
} 

int DofHandler::Dof(int nodeId) const {
    return 0;} // TODO

int DofHandler::nDofs() const {
    return nDofs_;
}

