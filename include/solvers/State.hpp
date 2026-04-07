#ifndef SOLVERS_STATE_HPP
#define SOLVERS_STATE_HPP

#include <Eigen/Dense>
#include <vector>

/**
 * @brief Stocke les valeurs numériques (DDL) de tous les champs à un instant T.
 */
class State {
private:
    Eigen::VectorXd values_; 
    double time_ = 0.0;
    int iteration_ = 0;

public:
    State() = default;

    explicit State(int totalDofs) 
        : values_(Eigen::VectorXd::Zero(totalDofs)) {}

    // --- Accès aux données globales ---
    const Eigen::VectorXd& getValues() const { return values_; }
    void setValues(const Eigen::VectorXd& newValues) { values_ = newValues; }

    // --- Gestion du temps ---
    double time() const { return time_; }
    void setTime(double t) { time_ = t; }
    int iteration() const { return iteration_; }
    void setIteration(int iter) { iteration_ = iter; }

    // --- Utilitaires de découpage (Mapping) ---
    int size() const { return static_cast<int>(values_.size()); }

    /**
     * @brief Extrait les valeurs d'un champ spécifique (ex: juste la pression).
     */
    Eigen::VectorXd getFieldValues(int offset, int size) const {
        return values_.segment(offset, size);
    }

    /**
     * @brief Permet de modifier uniquement un bloc (ex: initialiser la température).
     */
    void setFieldValues(int offset, const Eigen::VectorXd& fieldValues) {
        values_.segment(offset, fieldValues.size()) = fieldValues;
    }
};

#endif

