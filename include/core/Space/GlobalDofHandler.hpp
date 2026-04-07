#ifndef GLOBAL_DOF_HANDLER_HPP
#define GLOBAL_DOF_HANDLER_HPP

#include <vector>
#include "core/Space/LocalMapper.hpp"
#include "core/Geometry/Element.hpp"

/**
 * @brief Gère la numérotation globale à travers tous les champs physiques.
 * Permet de construire une matrice globale par blocs.
 */
class GlobalDofHandler {
private:
    std::vector<int> fieldOffsets_;
    int totalDofs_ = 0;

public:
    GlobalDofHandler() = default;

    /**
     * @brief Calcule les points de départ (offsets) de chaque champ dans la matrice globale.
     * @param fieldSizes Vecteur contenant le nombre total de DDLs de chaque champ.
     */
    void computeOffsets(const std::vector<int>& fieldSizes);

    /**
     * @brief Transforme les indices locaux d'un élément en indices globaux matriciels.
     * @tparam dim Dimension du problème (2 ou 3).
     * @param el L'élément fini en cours d'assemblage.
     * @param fieldId L'index du champ (0 pour le premier, 1 pour le second, etc.).
     * @param mapper Le mapper spécifique à ce champ.
     */
    template <size_t dim>
    std::vector<int> getGlobalIndices(const Element<dim>& el, int fieldId, const LocalMapper& mapper) const;

    // Getters
    int totalDofs() const { return totalDofs_; }
    int getOffset(int fieldId) const { return fieldOffsets_[fieldId]; }
};

#endif