cmake_minimum_required(VERSION 3.10)
project(FEM_Simulation_2.0 VERSION 1.0 LANGUAGES CXX)

# --- CONFIGURATION C++ ---
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- RECHERCHE DE EIGEN 3 ---
# Assure-toi qu'Eigen est installé sur ton système
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# --- RÉPERTOIRES D'INCLUSION ---
include_directories(include)

# --- RÉCUPÉRATION AUTOMATIQUE DES SOURCES ---
# On scanne récursivement tous les .cpp dans le dossier src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# --- CRÉATION DE L'EXÉCUTABLE ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- LIEN AVEC EIGEN ---
target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)

# --- OPTIONS DE COMPILATION ---
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4) # Warning level 4 sur Windows
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -O3) # Warnings + Optimisation sur Linux/Mac
endif()

# --- RÉPERTOIRE DE SORTIE DES RÉSULTATS ---
# Crée automatiquement le dossier 'results' s'il n'existe pas
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "results"
)