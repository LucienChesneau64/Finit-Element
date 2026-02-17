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
    // a ajouter source forme 
    // les conditions au bord BoundaryConditions
    // non linearForm
public:
    explicit Equation();

    Eigen::SparseMatrix<double> assembleStiffMatrix(const DiscreteSpace& discreteSpace);
    Eigen::VectorXd assembleb(const DiscreteSpace& discreteSpace);
    // methods 
};


