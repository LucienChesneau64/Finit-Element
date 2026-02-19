#include "Mesh.hpp"
#include "Element.hpp"

// classe interface pour fonctions p1, ... p2, .. , pn

template <size_t dim>

class BasisFunction {
    private:
        // localDof ???
    public:
        // constructeur?
        // destructeur
        ~BasisFunction() = default;
        // methods 

        // calcul de la valeur au point
        double computeValue(std::array<double,dim> x); // à corriger 
        // calcul du gradient 
        std::array<double,dim> computeGrad(const std::array<double,2>& dim); // ) corriger encore 
        // méthode de quadrature pour intégration??? 

        // localDof
        // 
        
        //
};

