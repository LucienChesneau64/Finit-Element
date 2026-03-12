#include "DiscreteSpace.hpp"
#include <vector>
#include <memory>

template<size_t dim> 

class MultiField {
    private:
        std::vector<std::shared_ptr<DiscreteSpace<dim>>> field_list;
    public:
        // constructor
        Multifield(std::vector<std::shared_ptr<DiscreteSpace<dim>>> field_list_): field_list(field_list_) {};
        // destructor
        ~MultiField() = default;
        // methods
        std::vector<std::shared_ptr<DiscreteSpace<dim>> getFields();

        void addField(std::shared_ptr<DiscreteSpace<dim>> newField);
};

