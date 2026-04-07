#ifndef CORE_FE_BASISFUNCTION_QUADRATURE_HPP
#define CORE_FE_BASISFUNCTION_QUADRATURE_HPP

#include <vector>
#include "core/FE/basisfunction/QuadraturePoint.hpp"

template <size_t dim>
class Quadrature {
private:
    std::vector<QuadraturePoint<dim>> points_;

public:
    Quadrature() = default;
    
    /**
     * @brief Construit une quadrature pour l'élément de référence (Simplexe).
     * @param order Ordre de précision souhaité.
     */
    explicit Quadrature(int order);

    // Uniquement les déclarations ici
    void addPoint(const QuadraturePoint<dim>& p);
    const std::vector<QuadraturePoint<dim>>& getPoints() const;
};

#endif
