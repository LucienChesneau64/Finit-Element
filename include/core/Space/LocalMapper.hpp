#ifndef CORE_SPACE_LOCAL_MAPPER_HPP
#define CORE_SPACE_LOCAL_MAPPER_HPP

#include <vector>
#include <cstddef>
#include "core/Geometry/Element.hpp"

/**
 * @brief Gère la correspondance entre les indices locaux d'un élément et les indices globaux.
 */
class LocalMapper {
private:
    int dofsPerNode_ = 0;
    int nTotalDofs_ = 0;
    std::vector<int> nodeToDof_;

public:
    LocalMapper() = default;
    
    /**
     * @brief Configure le mapper.
     */
    void build(int numNodes, int dofsPerNode);

    /**
     * @brief Renvoie les indices DDL globaux pour un élément donné.
     */
    template <size_t dim>
    std::vector<int> getLocalIndices(const Element<dim>& el) const;

    // Getters
    int nTotalDofs() const { return nTotalDofs_; }
    int dofsPerNode() const { return dofsPerNode_; }
    int getNodeDof(int nodeIdx) const { return nodeToDof_.at(nodeIdx); }
};

#endif