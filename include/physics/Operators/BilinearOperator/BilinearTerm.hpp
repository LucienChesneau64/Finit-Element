#ifndef BILINEAR_TERM_HPP
#define BILINEAR_TERM_HPP

#include <memory>
#include "physics/Operators/IBilinearOperator.hpp"

/**
 * @brief Structure de liaison pour un terme de la forme a(u, v).
 * Elle associe un opérateur mathématique à deux champs (test et trial).
 */
template <size_t dim>
struct BilinearTerm {
    // L'opérateur physique (ex: Laplace, Masse, Advection)
    std::shared_ptr<IBilinearOperator<dim>> op;

    // L'indice du champ pour les fonctions de TEST (les lignes de la matrice)
    int testFieldId;

    // L'indice du champ pour les fonctions d'ESSAI (les colonnes de la matrice)
    int trialFieldId;

    /**
     * @brief Constructeur complet.
     * @param o Pointeur vers l'opérateur.
     * @param testId ID du champ de destination (lignes).
     * @param trialId ID du champ d'origine (colonnes).
     */
    BilinearTerm(std::shared_ptr<IBilinearOperator<dim>> o, int testId, int trialId)
        : op(o), testFieldId(testId), trialFieldId(trialId) {}
};

#endif // BILINEAR_TERM_HPP