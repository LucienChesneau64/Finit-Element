#include "core/Geometry/Element.hpp"
#include <cmath>
#include <stdexcept>

template <size_t dim>
Element<dim>::Element(int type, int physId, const std::vector<int>& ids) 
    : nodeIds_(ids), type_(type), physicalId_(physId) {}

template <size_t dim>
Eigen::Matrix<double, dim, dim> Element<dim>::computeJacobian(const std::vector<Node<dim>>& allNodes) const {
    // Sécurité : Un Jacobien dim x dim nécessite dim+1 noeuds
    if (nodeIds_.size() < dim + 1) {
        throw std::runtime_error("Element::computeJacobian : Pas assez de noeuds pour le type d'element");
    }

    Eigen::Matrix<double, dim, dim> J;
    // On récupère les coordonnées du premier nœud (P0)
    const auto& P0 = allNodes[nodeIds_[0]].getCoords();
    
    for (size_t j = 0; j < dim; ++j) {
        // Les vecteurs colonnes de J sont (Pj - P0)
        const auto& Pj = allNodes[nodeIds_[j + 1]].getCoords();
        for (size_t i = 0; i < dim; ++i) {
            J(i, j) = Pj[i] - P0[i];
        }
    }
    return J;
}

template <size_t dim>
Eigen::Matrix<double, dim, dim> Element<dim>::getInverseJacobian(const std::vector<Node<dim>>& allNodes) const {
    return computeJacobian(allNodes).inverse();
}

template <size_t dim>
double Element<dim>::computeMeasure(const std::vector<Node<dim>>& allNodes) const {
    // Si c'est un élément de bord (ex: Ligne en 2D), sa mesure (aire) est nulle dans l'espace dim
    if (type_ < (int)dim) return 0.0; 

    double detJ = std::abs(computeJacobian(allNodes).determinant());
    
    // Volume d'un simplexe : det(J) / n!
    double fact = 1.0;
    for (size_t i = 1; i <= dim; ++i) fact *= i;
    
    return detJ / fact;
}

template <size_t dim>
Eigen::Vector<double, dim> Element<dim>::mapToGlobal(
    const Eigen::Vector<double, dim>& xi, 
    const std::vector<Node<dim>>& allNodes) const 
{
    const auto& P0_coords = allNodes[nodeIds_[0]].getCoords();
    Eigen::Vector<double, dim> P0;
    for(size_t i = 0; i < dim; ++i) P0(i) = P0_coords[i];

    return P0 + computeJacobian(allNodes) * xi;
}

// Instanciations explicites
template class Element<1>;
template class Element<2>;
template class Element<3>;

