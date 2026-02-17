#pragma once
#include <memory>
#include <vector>
#include <Eigen/Sparse>

#include "BilinearForm.hpp"
#include "LinearForm.hpp"
#include "DiscreteSpace.hpp"

class Equation {
private:
    std::vector<std::shared_ptr<BilinearForm>> bilinearForms;
    std::vector<std::shared_ptr<LinearForm>> linearForms;

public:
    explicit Equation();

    Eigen::SparseMatrix<double> assembleA(const DiscreteSpace& discreteSpace);
    Eigen::VectorXd assembleb(const DiscreteSpace& discreteSpace);
};

// changer equation qui n prend plus en membre mesh et IndexHandler.
// mais assmbleA et assembleB prend en entrée DiscreteSpace directmeent


