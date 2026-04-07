#ifndef PHYSICS_OPERATORS_LINEAR_OPERATOR_SOURCE_TERM_OPERATOR_HPP
#define PHYSICS_OPERATORS_LINEAR_OPERATOR_SOURCE_TERM_OPERATOR_HPP

#include "physics/Operators/LinearOperator/ILinearOperator.hpp"
#include <functional>

/**
 * @brief Opérateur pour le terme source f.
 * Calcule \int f * phi_i
 */
template <size_t dim>
class SourceTermOperator : public ILinearOperator<dim> {
private:
    // On utilise un std::function pour permettre des sources variables (x, y, z)
    std::function<double(const Eigen::Vector<double, dim>&)> sourceFunc_;

public:
    // Constructeur pour une source constante
    explicit SourceTermOperator(double constantValue) {
        sourceFunc_ = [constantValue](const Eigen::Vector<double, dim>&) { 
            return constantValue; 
        };
    }

    // Constructeur pour une source variable f(x)
    explicit SourceTermOperator(std::function<double(const Eigen::Vector<double, dim>&)> f) 
        : sourceFunc_(f) {}

protected:
    /**
     * @brief Implémentation du cœur : f(x) * phi_i(x)
     */
    double evalKernel(
        const DiscreteSpace<dim>& spaceTest,
        const QuadraturePoint<dim>& qp,
        const Element<dim>& el,
        int i
    ) const override;
};

#endif