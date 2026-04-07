#include "physics/Operators/LinearOperator/SourceTermOperator.hpp"

template <size_t dim>
double SourceTermOperator<dim>::evalKernel(
    const DiscreteSpace<dim>& spaceTest,
    const QuadraturePoint<dim>& qp,
    const Element<dim>& el,
    int i) const 
{
    // 1. Calculer les coordonnées réelles du point de quadrature x = Sum(Ni * Xi)
    const auto& nodes = spaceTest.mesh().getNodes();
    Eigen::Vector<double, dim> xReal = el.mapToGlobal(qp.point(), nodes);

    // 2. Évaluer la fonction de forme phi_i au point de quadrature
    double phi_i = spaceTest.shapeFunction().evaluate(i, qp);

    // 3. Calculer f(x) * phi_i(x)
    return sourceFunc_(xReal) * phi_i;
}

template class SourceTermOperator<2>;
template class SourceTermOperator<3>;
