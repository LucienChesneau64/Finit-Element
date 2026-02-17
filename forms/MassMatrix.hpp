#include "BilinearForm.hpp"


// coder MassMatrix qui hérite de bilinearForm. 
// coder -> localContribution

class MassMatrix : public BilinearForm {
    public:
        // constructeur
        MassMatrix(); // a préciser...

        double localContribution(
            const DiscreteSpace& discreteSpace, 
            const Element& e, 
            int local_i, 
            int local_j) const override;
};

