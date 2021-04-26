# PHYS516FINAL
<img src="BilayerAndProteinSurface.pdf">
[embed]https://github.com/cdalas2/PHYS516FINAL/blob/main/BilayerAndProteinSurface.pdf[/embed]

> A numerical boundary value method (BVM) for protein-induced bilayer deformation calculations

---

### Table of Contents

- [Problem Description](#problem-description)
- [Software](#software)
- [Benchmarks](#benchmarks)
- [Installation](#installation)
- [How To Compile And Run It](#how-to-compile-and-run-it)
- [References](#references)
- [Author Info](#author-info)

---

## Problem Description

#### Physical problem

How do lipid bilayer deformations induced by a protein depend on the protein's shape?

#### Framing of the problem in mathematics 

<img src="equations.png " width="1500" height="250">

We truncation the infinite series that represents the general form of the bilayer deformation field to a finite number of terms, N, and applying the boundary conditions along the protein-bilayer interface to form a linear system of boundary equations which can be solved for the coefficients A_n,B_n, where n = 0,1,2,...,N. Protein shape data can be obtained through either experimental measurements or molecular dynamics simulations. Since the late 1990's many protein structures have been highly resolved through x-ray crystallography. Many of these structures are catalogued in the Protein Data Bank (PDB) website https://www.rcsb.org. Adaptive point distributions are needed for accelerated convergence for many protein shapes of experimental and theoretical interest, which will be discussed in our manuscript.


#### Computational obstacles and remedy

Since Basset functions grow exponentially with increasing order n, floating point overflow issues and matrix conditioning issues manifest. We use Arblib library for arbitrary precision floating point calculations, choosing an appropriate precision to avoid overflow and to offset numerical instability when solving the linear system of boundary equations. Numerical algorithms to solve the linear system of boundary conditions that minimize adding anymore instability to the problem, as well as being parallelizable, are discussed in the manuscript.

[Back To The Top](#PHYS516FINAL)

---

## Software

We use only open-source software, so our approach is easily accessible to anyone with a laptop or desktop computer.

- C++
- Arblib library (version 2.17 or newer)
- Carlos_Membrane_Project
- OpenMP
- OpenMPI (if you want to do calculations for multiple protein systems)
- Paraview

[Back To The Top](#PHYS516FINAL)

---

## Benchmarks

#### OMP thread count speed up and efficiency benchmarks

<img src="speedup.png " width="500" height="375"> <img src="efficiency.png " width="500" height="375">

Our plots show performance benchmarks for a truncation length N = 62 and using floating point precision of about 200 decimal places.
We got almost a 5x speed up using only 8 threads. Efficiency decreases with increased thread count.

#### Boundary value method benchmarked against a hybrid of finite elements and discrete Kirchoff triangles method (FEDKTM)
The hybrid FEDKTM converges with decreasing average mesh length.
Using paraview we can create a pipeline to extract the length data of the mesh elements used in the FEDKTM. We average the mesh lengths and plot the FEDKTM calculations as a function of average mesh length. 

<img src="FEM_mesh.png " width="1000" height="600">

<img src="FEM_edges.png " width="1000" height="600">

<img src="FEM_celldata.png " width="1000" height="600">

After measuring the accuracy of the finite element method, we compared it with the converged BVM and found similar agreement to the accuracy of the FEDKTM, which shows the BVM appears to reliably converge to the correct result.

[Back To The Top](#PHYS516FINAL)

---

## Installation

1. Download github repo. This will contain the necessary make file, bash script, and source code files
2. Install Arblib library by Frederick Johansson (version 2.17 or newer). You can build from source [1] or download as a package through anaconda3.
3. Install OpenMP.
4. Install OpenMPI (if you want to do multiple protein runs).
5. Replace paths in make file to arblib library and header files.
6. Replace paths in bash script to arblib library and Carlos_membrane_project source files.
7. Replace paths in main source code file for the location of where the data output is to be saved.
8. Adjust OMP_NUM_THREADS environmental variable to the thread count wanted in the bash script.

[Back To The Top](#PHYS516FINAL)

---

## How To Compile And Run It

On a terminal one can compile a simulation by a make file provided. Then one can run the simulation by a bash script provided. Terminal/command lines are:

$ make

$ bash run_deformation.sl

[Back To The Top](#PHYS516FINAL)

---

## References

1. My manuscript (work in progress)

2. F. Johansson. Arb: efficient arbitrary-precision midpoint-radius interval arithmetic. IEEE Transactions on Computers, 66:1281-1292, 2017.

3. Leonardo Dagum and Ramesh Menon. Openmp: an industry standard api for shared-memory programming. Computational Science & Engineering, IEEE, 5(1):46-55, 1998.

4. openMPI (citation needed here)

5. Osman Kahraman, Peter D. Koch, William S. Klug, and Christoph A. Haselwandter. Architecture and function of mechanosensitive membrane protein lattices.              Scientific Reports, 6(1), Jan 2016.

6. Ayachit, Utkarsh, The ParaView Guide: A Parallel Visualization Application, Kitware, 2015, ISBN 978-1930934306


[Back To The Top](#PHYS516FINAL)

---

## Author Info

- LinkedIn - [Carlos Alas LI](https://www.linkedin.com/in/carlos-alas-6a4643160/)
- ResearchGate - [Carlos Alas RG](https://www.researchgate.net/profile/Carlos_Alas3)
This project was brought to life by Carlos D. Alas under the supervision of Christoph A. Haselwandter

[Back To The Top](#PHYS516FINAL)
