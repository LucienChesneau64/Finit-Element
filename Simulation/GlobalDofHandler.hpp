#include "DohHandler.hpp"
#include "MultiField.hpp"




class GlobalDofHandler {
    private:
        MultiField multifield
        std::vector<DofHandler> dofHandlerList; // liste des dofHandler qui se créeer a partir des discretSapce?

    public:
        // constructor
        // se construit avec multifield.
        // va stocker les dofhandlere qui vont se créer pour chaque DiscretSpace.
        // 
    // cette classe doit globaliser ls dof.
    // doit avoir une méthode pour retournr les indices d'un noeud à partir de son élement local et de son espace discret.

};

