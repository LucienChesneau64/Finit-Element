#ifndef CORE_GEOMETRY_NODE_HPP
#define CORE_GEOMETRY_NODE_HPP

#include <array>
#include <cstddef>

template <size_t dim>
class Node {
private:
    int id_;
    std::array<double, dim> coords_;

public:
    Node();
    Node(int id, const std::array<double, dim>& coords);

    int getId() const;
    const std::array<double, dim>& getCoords() const;
    double operator[](size_t i) const;
};

#endif