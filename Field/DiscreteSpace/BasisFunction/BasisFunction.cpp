#include "BasisFunction.hpp"

class P1 : public BasisFunction {
    private:

    public:
        // constructeur
        // methode heritée
        // calcul de la valeur au point.
        double computeValue(std::array<double,2> x); // a corriger pour template dim

};

