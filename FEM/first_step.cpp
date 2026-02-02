#include <vector>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <array>
#include <Eigen/Dense>

struct Node {
	int nodeId;
	double x, y;
};

class Element {
	private:
		std::array<int, 3> nodesId;
	public:
		// constructeur
		Element(const std::array<int, 3>& nodesId_): nodesId(nodesId_) {}
		// destructeur
		~Element() = default;
		// methods
		// geter
		std::array<int, 3> getNodesId();

		double computeAverageValue();
		double area();

};



class Mesh {
	private:
		std::vector<Node> nodes;
		std::vector<Element> elements;
	public:
		// constructeur
		Mesh(string path) {meshInit(std::string path)} // mettre lien d'un fichier 
		Mesh(std::vector<Node> nodes_, std::vector<Element> elements_): {}
		// destructeur
		~Mesh() = default;
		// methods (à compléter)
		std::vector<Elements> getElements();
		void meshInit(std::string path) // rentrer le lien du gmsh ou autre fichier
		void searchFrontierNodes(); // pour renvoyer les noeuds au bord , corriger void / renvoie quoi?
};


class DofHandler {
	private:
		// nodeId -> dof index
		std::unordered_map<int,int> nodeToDof;

		// nodes number
		int nbdofs = 0;
	
	public:
		DofHandler() = default;


		// construit numérotation à partir du Mesh
		void distributeDof(const Mesh& mesh);

		ind dof(int nodeId) const;

		int nDofs() const;
};

class Solver {

	public:
		// destructeur
		~Solver() = default;
		// methode virtuelle
		virtual Eigen::VectorXd solve(const Eigen::MatrixXd&A, const Eigen::VectorXd& b) = 0;
};

class IterativeSolver: public Solver {
	private:
		double error;
	public:
		// constructeur
		IterativeSolver(double error_): Solver(), error(error_) {};
		// destructeur
		~IterativeSolver() = default; 
		// minimize methods -> mieux appeler // gérer rhs, et vecteur x.
		virtual Eigen::VectorXd step(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x ) = 0; // methode interface
		Eigen::VectorXd solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& b);
};

Eigen::Vectorxd IterativeSolver::solve(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) {
	// pseudo code
	// x = choisi au hasard..
	// rhs = norm(Ax - b )
	// 
	// while( rhs > error) {
	// 	x = step(A,b);
	// 	rhs = Ax-b
	// 	}
	// return x;
}


class ConjugateGradient: public IterativeSolver {
	private:
		double eps;
	public:
		// methods 
		Eigen::VectorXd step(const Eigen::MatrixXd& A, const Eigen::VectorXd& b) override;
};


class BilinearForm {
	public:
		// destructor
		~BilinearForm() = default;
		

		// methods
		void assemble(const Mesh& mesh,
				const DofHandler& dof,
				Eigen::SparseMatrix<double>& A) const;
		
		virtual double localContribution(const Element& element, int i, int j) = 0; // à changer renvoie un scalaire
};

void BilinearForm::assemble(const Mesh& mesh, const DofHandler& dof, Eigen::SparseMatrix<double>& A) const {
	// boucle sur les éléments du mesh
	// boucle sur les noeuds de l'élément // double boucle pour avoir noeud n et m 
	// n et m donne (i,j) via dofHandler
	// A(i,j) += localContribution(element, n,m);
	for (auto e: mesh.getElements() ) {
		for (auto n: e.getNodesId()) {
			int i = DofHandler.dof(n);
			for (auto m: e.getNodesId()) {
				int j = DofHandler.dof(m);
				remplir A(i,j) += localContribution(e,i,j); // utiliser methode sparsity
			}
		}

	}
}

class LinearForm {
	// classe abstraite pour interface, forme linéaire
	public:
		// constructeur
		LinearForm();
		// destructeur
		~LinearForm() = default;

		Eigen::VectorXd assemble(const Mesh& mesh); // return b // changer avec dofHandler et prendre en entrée b)

		virtual void localContribution(const Elements& element, Eigen::VectorXd& b, int i) = 0;
};

void LinearForm::assemble(const Element& element, int i, int j) {
	// boucle sur les éléments du mesh
	// boucle sur les noeuds de l'élément n
	// n -> i via dofHandler
	// b(i) += localContribution(element, i)
};


// ====================================================
// rajout de l'évolution ==== a continuer... plus tard

class BoundaryCondition {
	// class abstraite  pour interface, condition au bord, doit etre associé avec liste des noeuds au bord sur lequel on applique -> coder méthode dans mesh pour les detecter.
	// applique une contrainte -> va se faire par multiplicateur de Lagrange
	// agit sur matrice A et rhs. ajout de dimension et/ou remplace les noeuds au bord par g(x) sur rhs
	// on commnce par dirichlet imposition g(x).
	public:
		void imposeb();
		void imposeA(); // susceptible de changer car argument qui change selon ls classes qui héritent.
};

class Scheme {
	// classe abstraite pour les différents schémas
	private:
		double dt;
	public:
		// constructeur
		Scheme(double dt_): dt(dt_) {}
		// destructeur
		~Scheme() = default;

		virtual void TimeStep() = 0; // prend en entrée quoi et renvoie quoi ????
}


class EulerScheme: public Scheme {
	public:
		EulerScheme(double dt_): Scheme(dt_) {}

		~EulerScheme() = default;
		
		void TimeStep() override;
};

//  ================================================


class Equation {
	// la classe qui "pose l'équation" Equation
 	//├── Mesh&
	//├── BilinearForm(s)
 	//├── LinearForm(s)
	//├── BoundaryConditions // à coder dans la suite.
 	//├── (TimeScheme) // faire une sous classe avec EvolutionEquation???
	//└── assemble()
	private:
		Mesh mesh; // changer en smart pointer également
		std::vector<std::shrared_ptr<BilinearForm>> bilinearForm_list; // changer en smart pointer
		std::vector<std::shared_ptr<LinearForm>> linearForm_list; // changer en smart pointer 
		std::vector<std::shared_ptr<BoundaryCondition>> boundaryCondition_list; // changer en smart pointer
	public:
		Equation(
				const Mesh& mesh_, 
				std::vector<std::shared_ptr<BilinearForm>> bilinearForm_list_, 
				std::vector<std::shared_ptr<LinearForm>> linearForm_list_,
				std::vector<std::shared<BoundaryCondition>> boundaryCondition_list_,
			): 

	{}

		// methods

		Eigen::SparseMatrixXd<double> assembleA();
		Eigen::VectorXd assembleb();
		void imposeBoundaryConditions(Eigen::SparseMatrixXd<double>& A, Eigen::VectorXd& b);
};





class Simulation {
 //Simulation
 //── Equation
 //── Solver
 //── ResultWriters
 //── Time loop -> à voir pour plus tard 
	private:
		std::shared_ptr<Equation> equation;	// mettre des smart pointer ici..
		std::shared_ptr<Solver> solver;
		std::vector<std::shared_ptr<ResultWriters>> writers;
		//TimeLoop integrator à compléter
	
	public:
		Simulation(std::shared_ptr<Equation> equation_, std::shared_ptr<Solver> solver_, std::vector<std::shared_ptr<Resultwriters>> writers_):
			equation(equation_), solver(solver_), writers(writers_) {}
		// destructeur
		~Simulation() = default;
		// methods

		void run(); // temps T dedans??? return std::vector<
};

void Simulation::run() {
	// while (time<T, time+dt)
	// A = equation.assembleA();
	// rhs = equation.assembleb();
	// equation.imposeBoundaryConditions(A,b);
	// 
	// solution = solver.solve(A,b);
	// on doit s'occuper de jeter A et b?



}

// écriture fonctions pour lire mesh/ à mettre dans classe mesh peut etre??? oui.


class PostProcessor {
	// pour calculer des énergies, des gradients, des normes ... ect
	// pour processer la solution. // a voir après
};

class ResultWriter {
	// écris les résultats à partir du vecteur de solution sur un fichier vtk.
	// class abstraite pour écrire différent résultats si jamais.
	// construit pour effctuer une photo tous les t temps.
	// methods
	// void write(Eigen::VectorXd solution, string txt/ vtk/ choisir adresse)
};



