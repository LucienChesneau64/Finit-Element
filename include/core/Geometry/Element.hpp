#ifndef CORE_GEOMETRY_ELEMENT_HPP
#define CORE_GEOMETRY_ELEMENT_HPP

#include <vector>
#include <Eigen/Dense>
#include "core/Geometry/Node.hpp"

template <size_t dim>
class Element {
private:
    std::vector<int> nodeIds_; 
    int type_;         // 1: Ligne, 2: Triangle, 4: Tetraedre (selon GMSH)
    int physicalId_;   // Ex: 101 pour le bord, 200 pour le domaine

public:
    // Nouveau constructeur adapté à GMSH
    Element(int type, int physId, const std::vector<int>& ids);

    int getType() const { return type_; }
    int getPhysicalId() const { return physicalId_; }
    const std::vector<int>& getNodeIndices() const { return nodeIds_; }
    
    // Calculs géométriques (Valides seulement si getType() == dim)
    Eigen::Matrix<double, dim, dim> computeJacobian(const std::vector<Node<dim>>& allNodes) const;
    Eigen::Matrix<double, dim, dim> getInverseJacobian(const std::vector<Node<dim>>& allNodes) const;
    double computeMeasure(const std::vector<Node<dim>>& allNodes) const;

    /**
     * @brief Passage du repère de référence (xi) au repère global (x)
     */
    Eigen::Vector<double, dim> mapToGlobal(
        const Eigen::Vector<double, dim>& xi, 
        const std::vector<Node<dim>>& allNodes) const;
};

#endif