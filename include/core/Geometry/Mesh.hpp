#ifndef CORE_GEOMETRY_MESH_HPP
#define CORE_GEOMETRY_MESH_HPP

#include <vector>
#include <string>
#include "core/Geometry/Node.hpp"
#include "core/Geometry/Element.hpp"

/**
 * @brief Gère le maillage global, les nœuds et les éléments de volume/bord.
 */
template <size_t dim>
class Mesh {
private:
    std::vector<Node<dim>> nodes_;
    std::vector<Element<dim>> elements_;
    int nNodes_;

public:
    Mesh();
    explicit Mesh(const std::string& path);

    // Getters
    const std::vector<Node<dim>>& getNodes() const;
    const std::vector<Element<dim>>& getElements() const;
    int getNNodes() const;

    /**
     * @brief Charge un fichier .msh (format GMSH 2.2).
     */
    void loadFromFile(const std::string& path);

    /**
     * @brief Récupère les IDs globaux des nœuds appartenant à une frontière physique.
     */
    std::vector<int> getNodesOnBoundary(int boundaryId) const;
};

#endif

