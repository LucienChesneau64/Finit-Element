#ifndef CORE_SPACE_MULTI_FIELD_HPP
#define CORE_SPACE_MULTI_FIELD_HPP

#include <vector>
#include <string>
#include <memory>

#include "core/Space/DiscreteSpace.hpp"
#include "core/Space/GlobalDofHandler.hpp"

template <size_t dim>
class MultiField {
private:
    struct FieldInfo {
        std::string name;
        std::shared_ptr<DiscreteSpace<dim>> space;
        int offset; 
    };
    
    std::vector<FieldInfo> fields_;
    GlobalDofHandler dofHandler_; 
    int totalSize_;

public:
    MultiField() : totalSize_(0) {}

    int addField(const std::string& name, std::shared_ptr<DiscreteSpace<dim>> space);
    void updateDofs();
    
    int totalSize() const { return totalSize_; }
    
    // --- Getters indispensables pour la compilation et le VTK ---
    const GlobalDofHandler& getDofHandler() const { return dofHandler_; }
    std::shared_ptr<DiscreteSpace<dim>> getSpace(int fieldId) const { return fields_[fieldId].space; }
    int getFieldOffset(int fieldId) const { return fields_[fieldId].offset; }
    

    // Ajoutés pour que VTKWriter.cpp compile :
    int NbFields() const { return static_cast<int>(fields_.size()); }
    std::string getFieldName(int fieldId) const { return fields_[fieldId].name; }
};

#endif