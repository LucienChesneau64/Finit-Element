#include "BilinearForm.hpp"


// coder MassMatrix qui hérite de bilinearForm. 
// coder -> localContribution


template<size_t dim>
class MassMatrix : public BilinearForm {
    public:
        // constructeur
        MassMatrix(); // a préciser...

        double localContribution(
            const DiscreteSpace<dim>& discreteSpace, 
            const Element<dim>& e, 
            int local_i, 
            int local_j) const override;
};

