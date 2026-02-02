#pragma once
#include <array>

class Element {
private:
    std::array<int,3> nodeIds;

public:
    explicit Element(const std::array<int,3>& ids);

    const std::array<int,3>& getNodeIds() const;

    double area() const;
};


