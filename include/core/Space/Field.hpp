#ifndef FIELD_HPP
#define FIELD_HPP

#include <memory>
#include <string>
#include "core/Space/DiscreteSpace.hpp"
#include "core/Space/LocalMapper.hpp"

/**
 * @brief Représente une variable physique (U, V, P, T) dans le système.
 * Lie la définition mathématique (Espace) à sa logistique (Mapper).
 */
template <size_t dim>
struct Field {
    std::string name;
    int id;

    // L'espace de discrétisation (Maillage + Fonctions de forme)
    std::shared_ptr<DiscreteSpace<dim>> space;

    // Le traducteur (indices de nœuds -> indices de matrice globale)
    LocalMapper mapper;

    /**
     * @brief Constructeur d'un champ physique.
     * @param s Pointeur partagé vers l'espace discret.
     * @param n Nom du champ (ex: "Temperature").
     * @param identifier ID unique du champ dans le système.
     */
    Field(std::shared_ptr<DiscreteSpace<dim>> s, const std::string& n, int identifier);
};

#endif
