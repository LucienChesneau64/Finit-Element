#include "BasisFunction.hpp"

template <size_t dim>
class P1: public BasisFunction {
    public:
        // constructeur
        P1(): nDofPerNodes(int 1) {};

        const double value(const std::array<double, dim>& x, const Element& elem) override;
        const std::array<double, dim> gradValue(const std::array<double, dim>& x, const Element& elem) override;
};

// utilisation de Quadrature??

