#pragma once
#include <array>

template<size_t dim>

struct Node {
    int id;
    std::array<double, dim> coords;
};

