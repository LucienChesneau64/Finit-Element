#ifndef CORE_FE_BASISFUNCTION_QUADRATURE_POINT_HPP
#define CORE_FE_BASISFUNCTION_QUADRATURE_POINT_HPP

#include <Eigen/Dense>

/**
 * @brief Point d'intégration numérique dans l'élément de référence.
 */
template <size_t dim>
class QuadraturePoint {
private:
    Eigen::Vector<double, dim> coords_;
    double weight_;

public:
    QuadraturePoint() : weight_(0.0) { coords_.setZero(); }
    
    QuadraturePoint(const Eigen::Vector<double, dim>& c, double w)
        : coords_(c), weight_(w) {}

    // Accès aux données brutes
    const Eigen::Vector<double, dim>& point() const { return coords_; }
    double weight() const { return weight_; }

    // Raccourcis pour les coordonnées de référence (r, s, t)
    double r() const { return coords_[0]; }
    double s() const { 
        if constexpr (dim > 1) return coords_[1]; 
        else return 0.0; 
    }
    double t() const { 
        if constexpr (dim > 2) return coords_[2]; 
        else return 0.0; 
    }
};

#endif