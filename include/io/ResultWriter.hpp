#ifndef IO_RESULT_WRITER_HPP
#define IO_RESULT_WRITER_HPP

#include <string>
// Correction de l'inclusion selon ton arborescence (tree)
#include "solvers/State.hpp"
#include "core/Space/MultiField.hpp"

/**
 * @brief Interface abstraite pour l'export des résultats (VTK, HDF5, etc.).
 * Permet d'ajouter n'importe quel format de sortie à la simulation.
 */
template <size_t dim>
class ResultWriter {
protected:
    std::string baseFilename_;

public:
    /**
     * @brief Constructeur avec le nom de base du fichier (sans extension).
     */
    explicit ResultWriter(const std::string& filename) : baseFilename_(filename) {}
    
    virtual ~ResultWriter() = default;

    /**
     * @brief Écrit l'état actuel (temps, itération, valeurs) dans un fichier.
     * @param state Contient les valeurs numériques.
     * @param mf Contient la structure (maillage, noms des champs).
     */
    virtual void write(const State& state, const MultiField<dim>& mf) = 0;
};

#endif