#include "physics/Operators/BilinearOperator/MassMatrix.hpp"

template <size_t dim>
double MassOperator<dim>::evalKernel(
    const DiscreteSpace<dim>& spaceTest,
    const DiscreteSpace<dim>& spaceTrial,
    const QuadraturePoint<dim>& qp,
    const Element<dim>& el,
    int i, int j) const 
{
    double phi_i = spaceTest.shapeFunction().evaluate(i, qp);
    double phi_j = spaceTrial.shapeFunction().evaluate(j, qp);

    return density_ * phi_j * phi_i;
}

template class MassOperator<2>;
template class MassOperator<3>;

