#ifndef IO_VTK_WRITER_HPP
#define IO_VTK_WRITER_HPP

#include "io/ResultWriter.hpp"
#include <fstream>
#include <string>

/**
 * @brief Exportateur au format VTK Legacy (.vtk) pour ParaView.
 */
template <size_t dim>
class VTKWriter : public ResultWriter<dim> {
public:
    // Utilise le constructeur de la classe mère ResultWriter
    using ResultWriter<dim>::ResultWriter;

    /**
     * @brief Génère le fichier VTK pour l'état actuel.
     */
    void write(const State& state, const MultiField<dim>& mf) override;

private:
    /**
     * @brief Helper pour déterminer le type de cellule VTK (5=Triangle, 10=Tetra).
     */
    int getVTKCellType() const;
    
    /**
     * @brief Helper pour le nombre de nœuds par élément (3 ou 4).
     */
    int getNodesPerElement() const;
};

#endif