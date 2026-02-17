#include "ResultWriter.hpp"
#include "DiscreteSpace.hpp"
class HTF5Writer : public Resultwriter {
    private:
        std::string filename;

    public:
        // constructeur
        HTF5Writer(const std::string& filename);

        void write(
            const Mesh& mesh,
            const IndexHandler& dof,
            const Eigen::VectorXd solution
        ) override;
};

// get Mesh et IndexHandler from DiscreteSpace.