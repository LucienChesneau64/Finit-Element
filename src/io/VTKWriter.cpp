#include "io/VTKWriter.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

template <size_t dim>
int VTKWriter<dim>::getVTKCellType() const {
    return (dim == 2) ? 5 : 10; // 5: VTK_TRIANGLE, 10: VTK_TETRA
}

template <size_t dim>
int VTKWriter<dim>::getNodesPerElement() const {
    return (dim == 2) ? 3 : 4;
}

template <size_t dim>
void VTKWriter<dim>::write(const State& state, const MultiField<dim>& mf) {
    // 1. Préparation du nom de fichier
    std::stringstream ssName;
    ssName << this->baseFilename_ << "_" << std::setfill('0') << std::setw(5) << state.iteration() << ".vtk";
    std::string filename = ssName.str();

    std::ofstream file(filename); // <-- C'est cette ligne qui manquait !
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file: " << filename << std::endl;
        return;
    }

    const auto& mesh = mf.getSpace(0)->mesh();
    const auto& allNodes = mesh.getNodes();
    const auto& allElements = mesh.getElements();

    // --- FILTRAGE DES ELEMENTS ---
    // On ne veut que les volumes (Triangles en 2D, Tetras en 3D)
    int targetType = (dim == 2) ? 2 : 4;
    std::vector<const Element<dim>*> volumeElements;
    for (const auto& el : allElements) {
        if (el.getType() == targetType) {
            volumeElements.push_back(&el);
        }
    }

    // --- VTK HEADER ---
    file << "# vtk DataFile Version 3.0\n";
    file << "FEM Simulation Results - Time: " << state.time() << "\n";
    file << "ASCII\n";
    file << "DATASET UNSTRUCTURED_GRID\n";

    // --- POINTS ---
    file << "POINTS " << allNodes.size() << " double\n";
    for (const auto& node : allNodes) {
        const auto& coords = node.getCoords();
        file << coords[0] << " " << (dim >= 2 ? coords[1] : 0.0) << " " << (dim == 3 ? coords[2] : 0.0) << "\n";
    }

    // --- CELLS ---
    int nNodesPerEl = getNodesPerElement();
    file << "CELLS " << volumeElements.size() << " " << volumeElements.size() * (nNodesPerEl + 1) << "\n";
    for (const auto* el : volumeElements) {
        const auto& nodeIndices = el->getNodeIndices();
        file << nNodesPerEl;
        for (int id : nodeIndices) {
            file << " " << id;
        }
        file << "\n";
    }

    // --- CELL_TYPES ---
    file << "CELL_TYPES " << volumeElements.size() << "\n";
    int cellType = getVTKCellType();
    for (size_t i = 0; i < volumeElements.size(); ++i) {
        file << cellType << "\n";
    }

    // --- POINT_DATA ---
    file << "POINT_DATA " << allNodes.size() << "\n";
    
    for (int fId = 0; fId < mf.NbFields(); ++fId) {
        auto space = mf.getSpace(fId);
        std::string fieldName = mf.getFieldName(fId);
        int offset = mf.getFieldOffset(fId);
        const auto& mapper = space->getMapper(); // Récupère le mapper de cet espace

        file << "SCALARS " << fieldName << " double 1\n";
        file << "LOOKUP_TABLE default\n";

        for (int i = 0; i < (int)allNodes.size(); ++i) {
            // Demande au mapper l'index du nœud 'i'
            // (En P1, un nœud = un DDL, mais l'index n'est pas forcément 'i')
            int localDofIdx = mapper.getNodeDof(i); 
            
            // On récupère la valeur avec l'offset global du champ
            double val = state.getValues()(offset + localDofIdx);
            
            file << val << "\n";
        }
    }

    file.close();
    std::cout << "[VTK] Exported: " << filename << std::endl;
}

// Instanciations explicites
template class VTKWriter<2>;
template class VTKWriter<3>;