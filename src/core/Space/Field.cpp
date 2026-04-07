#include "core/Space/Field.hpp"

template <size_t dim>
Field<dim>::Field(std::shared_ptr<DiscreteSpace<dim>> s, const std::string& n, int identifier)
    : name(n), id(identifier), space(s) 
{
    // Initialisation automatique du mapper à partir des données de l'espace
    // On utilise getNNodes() défini dans Mesh.hpp
    mapper.build(s->mesh().getNNodes(), s->getDofsPerNode());
}

// Instanciations explicites pour le linker
template struct Field<2>;
template struct Field<3>;

