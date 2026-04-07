#include "core/FE/basisfunction/Quadrature.hpp"

template <size_t dim>
Quadrature<dim>::Quadrature(int order) {
    if constexpr (dim == 2) {
        // Simplexe unité (Triangle) : Aire = 0.5
        if (order <= 2) {
            // Règle des milieux des arêtes (Ordre 2)
            // Somme des poids doit être égale à l'aire du triangle réf (0.5)
            double w = 1.0 / 6.0; 
            addPoint(QuadraturePoint<2>(Eigen::Vector2d(0.5, 0.0), w));
            addPoint(QuadraturePoint<2>(Eigen::Vector2d(0.5, 0.5), w));
            addPoint(QuadraturePoint<2>(Eigen::Vector2d(0.0, 0.5), w));
        } else {
            // Par défaut : Centre de gravité (Ordre 1)
            addPoint(QuadraturePoint<2>(Eigen::Vector2d(1.0/3.0, 1.0/3.0), 0.5));
        }
    }
    else if constexpr (dim == 3) {
        // Simplexe unité (Tétraèdre) : Volume = 1/6
        if (order >= 1) {
            // Centre de gravité (Ordre 1)
            // Poids = Volume du tétraèdre de référence = 1/6
            addPoint(QuadraturePoint<3>(Eigen::Vector3d(0.25, 0.25, 0.25), 1.0/6.0));
        }
    }
}

template <size_t dim>
void Quadrature<dim>::addPoint(const QuadraturePoint<dim>& p) {
    points_.push_back(p);
}

template <size_t dim>
const std::vector<QuadraturePoint<dim>>& Quadrature<dim>::getPoints() const {
    return points_;
}

// Instanciations explicites pour le linker
template class Quadrature<2>;
template class Quadrature<3>;