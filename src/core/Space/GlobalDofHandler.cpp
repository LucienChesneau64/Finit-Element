#include "core/Space/GlobalDofHandler.hpp"

void GlobalDofHandler::computeOffsets(const std::vector<int>& fieldSizes) {
    fieldOffsets_.clear();
    int currentOffset = 0;
    
    // On stocke le début de chaque champ
    for (int size : fieldSizes) {
        fieldOffsets_.push_back(currentOffset);
        currentOffset += size;
    }
    
    // Le dernier offset + sa taille donne le total de lignes/colonnes
    totalDofs_ = currentOffset;
}

template <size_t dim>
std::vector<int> GlobalDofHandler::getGlobalIndices(const Element<dim>& el, int fieldId, const LocalMapper& mapper) const {
    // 1. On récupère les indices relatifs au champ (ex: 0, 1, 2...)
    std::vector<int> indices = mapper.getLocalIndices(el);
    
    // 2. On applique le décalage pour le bloc correspondant
    int offset = fieldOffsets_[fieldId];
    for (int& idx : indices) {
        idx += offset;
    }
    
    return indices;
}

// Instanciations explicites pour le linker
template std::vector<int> GlobalDofHandler::getGlobalIndices<2>(const Element<2>& el, int fieldId, const LocalMapper& mapper) const;
template std::vector<int> GlobalDofHandler::getGlobalIndices<3>(const Element<3>& el, int fieldId, const LocalMapper& mapper) const;

