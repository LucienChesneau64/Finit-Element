#pragma once
#include <memory>
#include <vector>
#include <Eigen/Sparse>

#include "Mesh.hpp"
#include "BilinearForm.hpp"
#include "LinearForm.hpp"
#include "DofHandler.hpp"

class Equation {
private:
    Mesh mesh;
    DofHandler dof;

    std::vector<std::shared_ptr<BilinearForm>> bilinearForms;
    std::vector<std::shared_ptr<LinearForm>> linearForms;

public:
    explicit Equation(const Mesh& mesh_);

    Eigen::SparseMatrix<double> assembleA();
    Eigen::VectorXd assembleb();
};

