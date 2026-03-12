#include "MultiField.hpp"

std::vector<std::shared_ptr<DiscreteSpace> Multifield::getFields() {


}

void Multifield::addField(const std::shared_ptr<DiscretSpace> newField) {
    field_list.pusback(newField);
}

