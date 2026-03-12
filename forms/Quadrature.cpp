#include <vector>


template <size_t dim>

struct Qpoints {
    // points de référence de l'élément élémentaire.
    std::array<dim, double> coords;
    // poids associé.
    double weight;
};

// est une classe de données, qui gère seulement les points et poids associés.
// c'est ce qui caractérise justement une technique de quadrature.


class Quadrature {
    private:
        // liste des Qpoints
        std::vector<Qpoints> points;
    public:
        // constructeur.
        Quadrature(std::vector<Qpoints> points_): points(points_) {verificator()}
        // destructor
        ~Quadrature() default = 0;
        // verificator. sum of weight = 1.
        void verification_weight(); // appel destructor si mauvais pour pas laisser passer.
        // geter
        std::vector<Qpoints> getPoints();
};




