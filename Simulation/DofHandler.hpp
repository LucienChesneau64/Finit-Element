#pragma once
#include "DiscreteSpace.hpp"

template <size_t dim>
class DofHandler
{
private:
    nodeToDof;
    int nDofs_ = 0;
    void distributeDofHandler(const DiscreteSpace<dim>& Space);

public:
    // constructeur
    DofHandler(const DiscreteSpace<dim>& Space) {distributeDofHandler(Space)}
    // destructeur
    ~DofHandler() = default;

    // methdods 
    int dof(int nodeId) const;
    int nDofs() const;
};


// doit fournir le nombre de degré de liberté, donc en faire son calcul.
// par exemple:
// P2 -> 1 dof
// field -> 2 dof
// charger par bloc: dof(noeud i) -> renvoie i*(1+2). 
// total dof => nombre noeud * dof 
// au distributeDofHandler, a chaque boucle de noeud -> nDofs += dof / avec dof = FieldParameter * BasisFunction.
// 