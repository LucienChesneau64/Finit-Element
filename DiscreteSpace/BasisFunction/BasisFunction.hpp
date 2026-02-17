#include "Mesh.hpp"
#include "Element.hpp"

// classe abstraite pour fonctions p1, ... p2, .. , pn

class BasisFunction {
    private:

    public:
        // constructeur?

        // destructeur
        ~BasisFunction() = default;
        // methods 

        // calcul de la valeur au point
        double computeValue(std::array<double,2> x); // à corriger 
        // calcul du gradient 
        std::array<double,2> computeGrad(const std::array<double,2>& x); // ) corriger encore 
        // méthode de quadrature pour intégration??? 



};

// à inclure dans Forme Linéaire et Bilinéaire dans fonctions assemblagle, car assemblage dépend des fnctions de bases.

