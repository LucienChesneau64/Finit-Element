#include "Element.hpp"

Element::Element(const std::array<int,3>& ids)
    : nodeIds(ids) {}

const std::array<int,3>& Element::getNodeIds() const {
    return nodeIds;
}

double Element::area() const {
    return 0.0; // TODO
}


