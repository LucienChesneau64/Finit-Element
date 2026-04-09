# MultiPhysics Finite Element Method (FEM) Engine

This project is a high-performance **MultiPhysics FEM Engine** written in modern C++. It is designed as a generic numerical laboratory to solve complex Partial Differential Equations (PDEs), from stationary Poisson problems to transient coupled systems.

## Key Features

* **Generic MultiPhysics Framework**: Designed to handle scalar, vector, and tensor fields simultaneously (e.g., Velocity-Pressure-Temperature coupling).
* **Operator-Based Physics**: Modular `Operator` classes. Implement physical terms (Laplacian, Advection, Source) independently and assemble them to build any PDE.
* **PDE-Agnostic Architecture**: The core engine is independent of the physics. Easily implement any weak form: Navier-Stokes, Elasticity, or Maxwell equations.
* **Evolution & Transient Systems**: Built-in support for time-dependent PDEs with advanced time-stepping schemes (Euler, Crank-Nicolson, etc.).
* **Advanced Boundary Conditions (BCs)**: 
    * Support for **Dirichlet** and **Neumann** conditions.
    * **Face-ID Management**: Precise control over boundary surfaces using Mesh IDs to assign values (e.g., constant u=1 or custom functions) to specific faces.
* **Dynamic MultiField Management**: Flexible management of discrete spaces, allowing for the addition of custom fields and degrees of freedom (DoFs) on the fly.
* **Mathematical Validation (MMS)**: Integrated `Task` system for automated convergence analysis using L1, L2, and L-infinity error norms.
* **Professional Data Export**: 
    * **VTK/XML** format for high-end visualization in **ParaView**.
    * **CSV Metadata** for quantitative error tracking and convergence plotting.

---

<p align="center">
  <img width="547" height="556" alt="dirichlet" src="https://github.com/user-attachments/assets/e765430a-afda-4ef6-b6c5-ae4f89d42164" />
</p>

---

## Project Architecture

The codebase follows a modular design, allowing you to plug in new physics without modifying the numerical core:

* `src/core/` : The "Numerical Brain" — Mesh handling, Shape Functions, Quadrature rules, Boundary ID management, and MultiField discrete space structures.
* `src/physics/` : **Operator-based implementation**. Contains the logic for discrete operators (Laplacian, Gradient, etc.) and specific PDE definitions.
* `src/solvers/` : Linear/Non-linear solvers, Time-evolution schemes, and global `State` management.
* `src/tasks/` : Post-processing pipeline and validation tools (L2 error, flux calculation, etc.).
* `src/io/` : High-performance writers (`ResultWriter`, `CsvTaskWriter`, `TaskWriter`).
* `examples/` : Ready-to-run benchmarks, from simple Heat Diffusion to complex Coupled Systems.

---

## Validation & Convergence


*(Detailed validation and convergence plots coming soon ).*

---

## Installation & Usage

### Prerequisites
* **C++17/20** compatible compiler (GCC 9+, Clang 10+, MSVC 2019+)
* **CMake 3.15+**

### Compilation & Build
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make -j4
