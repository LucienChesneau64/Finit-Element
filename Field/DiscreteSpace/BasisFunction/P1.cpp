#include "P1.hpp"

template <size_t dim>
const double P1<dim>::value(const std::array<double, dim>& x, const Element<dim>& elem) {
    // to implement
    // get nodes of element.

    return value;
}

template <size_t dim>
const std::array<double, dim> gradValue(const std::array<double, dim>& x, const Element<dim>& elem) {
    // to implement
    // get nodes of element.
    return grad;
}