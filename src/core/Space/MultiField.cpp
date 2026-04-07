#include "core/Space/MultiField.hpp"
#include <stdexcept>

template <size_t dim>
int MultiField<dim>::addField(const std::string& name, std::shared_ptr<DiscreteSpace<dim>> space) {
    int newId = static_cast<int>(fields_.size());
    
    // On ajoute le champ. L'offset sera calculé plus tard dans updateDofs()
    fields_.push_back({name, space, 0});
    
    return newId;
}

template <size_t dim>
void MultiField<dim>::updateDofs() {
    int currentOffset = 0;
    
    for (auto& field : fields_) {
        field.offset = currentOffset;
        // On cumule les Degrés De Liberté (DDL) de chaque espace
        currentOffset += field.space->getNbTotalDofs(); // Vérifie que cette méthode existe dans DiscreteSpace
    }
    
    totalSize_ = currentOffset;
}

// Les méthodes totalSize(), getDofHandler() et getSpace() sont écrites "inline" 
// directement dans le MultiField.hpp. On ne doit PAS les redéfinir ici !

// --- Instanciations explicites ---
template class MultiField<2>;
template class MultiField<3>;