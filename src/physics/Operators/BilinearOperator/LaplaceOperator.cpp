#include "physics/Operators/BilinearOperator/LaplaceOperator.hpp"
#include <Eigen/Dense>

template <size_t dim>
double LaplaceOperator<dim>::evalKernel(
    const DiscreteSpace<dim>& spaceTest,
    const DiscreteSpace<dim>& spaceTrial,
    const QuadraturePoint<dim>& qp,
    const Element<dim>& el,
    int i, int j) const 
{
    Eigen::Vector<double, dim> gradRefI = spaceTest.shapeFunction().evaluateLocalGradient(i, qp);
    Eigen::Vector<double, dim> gradRefJ = spaceTrial.shapeFunction().evaluateLocalGradient(j, qp);

    const auto& nodes = spaceTest.mesh().getNodes();
    
    Eigen::Matrix<double, dim, dim> J = el.computeJacobian(nodes);
    Eigen::Matrix<double, dim, dim> invJT = J.inverse().transpose();

    Eigen::Vector<double, dim> gradRealI = invJT * gradRefI;
    Eigen::Vector<double, dim> gradRealJ = invJT * gradRefJ;

    return diffusivity_ * gradRealJ.dot(gradRealI);
}

template class LaplaceOperator<2>;
template class LaplaceOperator<3>;

