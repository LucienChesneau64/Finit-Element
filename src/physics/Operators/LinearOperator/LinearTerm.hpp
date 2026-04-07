#ifndef LINEAR_TERM_HPP
#define LINEAR_TERM_HPP

#include <memory>
#include "physics/Operators/ILinearOperator.hpp"

/**
 * @brief Structure de liaison pour un terme de la forme L(v) = \int f*v.
 * Associe un opérateur linéaire (source, force) à un champ de test.
 */
template <size_t dim>
struct LinearTerm {
    // L'opérateur physique (ex: Source de chaleur, Gravité)
    std::shared_ptr<ILinearOperator<dim>> op;

    // L'indice du champ qui REÇOIT ce terme (ex: 0 pour la Vitesse)
    int testFieldId;

    /**
     * @brief Constructeur.
     * @param o Pointeur vers l'opérateur linéaire.
     * @param testId ID du champ dans le MultiField.
     */
    LinearTerm(std::shared_ptr<ILinearOperator<dim>> o, int testId)
        : op(o), testFieldId(testId) {}
};

#endif // LINEAR_TERM_HPP