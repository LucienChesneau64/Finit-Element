#include "Mesh.hpp"
#include "Element.hpp"

// classe interface pour fonctions p1, ... p2, .. , pn, p0.

template <size_t dim>

class BasisFunction
{
private:
    int nDofPerNodes;
public:
    // destructeur
    ~BasisFunction() = default;
    // methods

    // évaluation du gradient en un point.
    virtual const double value(const std::array<double, dim>& x, const Element& elem) = 0; // pour évaluer le point avec son élément correspondant.
    // évaluation du gradient en un point.
    virtual const std::array<double, dim> gradValue(const std::array<double, dim>& x, elem) = 0; // classe virtuel pour chaque fonction de base.

    // renvoie le nombre de degrés de liberté nécessaire. pour plus tard.
    const int getnDofPerNodes() const;
};
