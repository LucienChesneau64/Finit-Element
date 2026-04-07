#include "core/Space/LocalMapper.hpp"

void LocalMapper::build(int numNodes, int dofsPerNode) {
    this->dofsPerNode_ = dofsPerNode;
    this->nTotalDofs_ = numNodes * dofsPerNode;
    
    // Initialisation de la table
    nodeToDof_.resize(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        // En scalaire (Température), le DDL i est le nœud i
        nodeToDof_[i] = i * dofsPerNode; 
    }
}


template <size_t dim>
std::vector<int> LocalMapper::getLocalIndices(const Element<dim>& el) const {
    // On récupère les IDs des nœuds connectés à l'élément
    const auto& nodeIndices = el.getNodeIndices();
    
    std::vector<int> indices;
    indices.reserve(nodeIndices.size() * dofsPerNode_);

    for (int nodeId : nodeIndices) {
        for (int i = 0; i < dofsPerNode_; ++i) {
            // Formule : (ID du noeud * nombre de composantes) + décalage de la composante
            indices.push_back(nodeId * dofsPerNode_ + i);
        }
    }
    return indices;
}

// --- Instanciations explicites pour le linker ---
template std::vector<int> LocalMapper::getLocalIndices<2>(const Element<2>& el) const;
template std::vector<int> LocalMapper::getLocalIndices<3>(const Element<3>& el) const;