#pragma once
#include <unordered_map>
#include "Mesh.hpp"

class DofHandler {
private:
    std::unordered_map<int,int> nodeToDof;
    int nDofs_ = 0;

public:
    void distributeDofs(const Mesh& mesh);

    int dof(int nodeId) const;
    int nDofs() const;
};


