# PHYS516FINAL
<img src="Lattice.png " width="550" height="500">

> A kinetic monte carlo (KMC) method for predicting the trajectories of freely diffusing particles in heterogeneous media applied to several problems in biophysics

---

### Table of Contents

- [Problem Description](#problem-description)
- [Stochastic Lattice Model And Subvolume Kinetic Monte Carlo](#stochastic-lattice-model-and-subvolume-kinetic-monte-carlo)
- [Results](#results)
- [Software And Installation](#software-and-installation)
- [How To Compile And Run It](#how-to-compile-and-run-it)
- [Other Biophysics Problems](#other-biophysics-problems)
- [References](#references)
- [Author Info](#author-info)

---

## Problem Description

#### Emerin proteins
We will look at the phenomenon of monomer emerin proteins freely diffusing through an inhomogenous nuclear membrane surface where the heterogeneity is due to the clustering of the emerin protein in the form of nanodomains with spacially different diffusion rates. We wish to track the trajectories of the emerin proteins. The motion of the emerin proteins is governed by diffusion through the membrane lipids. Within the nanodomain, the diffusion coefficient is about an order of magnitude slower than that outside of it, due to the clustering of emerin proteins there. PROJECT NOTES--->
<img src="KMC_ProjectNotes.pdf ">


[Back To The Top](#PHYS516FINAL)

---

## Stochastic Lattice Model And Subvolume Kinetic Monte Carlo

We use the stochastic lattice model described in the reference paper {CITATION NEEDED HERE}.
1. Domain patch is divided into K = 1600 cells.
2. System start state is M = 1600 particles uniformly distrubed along all cells; so 1 particle in each cell.
3. Calculate transition rates W(N,\tau) of each lattice cell.
4. Assign event times to each lattice cell using random numbers and the transition rates. Only one particle 
  hop is simulated at each iteration and so the system of particles is evolved 1 hop at a time.
5. Sort lattice cells by their event time in a binary min heap.
6. 1st iteration will occur in the binary tree root node lattice cell of this heap.
7. Randomly pick one the nearest neighbors of this lattice cell, for the particle to hop into.
8. Update lattice occupancy numbers and the transition rates of the lattice cells involved.
9. Calculate new event times for the lattice cells involved.
10. Re-sort the binary heap if necessary.
11. Repeat 6-10 for subsequent iteration.


[Back To The Top](#PHYS516FINAL)

---

## Results
<img src="KMC_freeDiffusion.png " width="550" height="500">


[Back To The Top](#PHYS516FINAL)

---

## Software And Installation

Download github repo. This will contain the necessary make file and source code files for code compilation of C code.

[Back To The Top](#PHYS516FINAL)

---

## How To Compile And Run It

On a terminal one can compile a simulation by a make file provided. Then one can run the simulation by executing the executable generated, KMC. This will print the result to the terminal or command prompt. In practice, we redirect the output to an output file to save the data run.

$ make

$ ./KMC > KMC.out

[Back To The Top](#PHYS516FINAL)

---

## Other Biophysics Problems

#### 1) Bacteria hopping and trapping
Many bacteria swim in the form of a random walk in order to sample an area and build a gradient towards food or towards (away from) a specific chemical. Sometimes these bacteria can encounter media that limits their mobility, such as when traveling across a porous surface or into a fluid domain of a different viscosity. When the bacteria is in a pore it is described as being trapped. When the bacteria finds a way out of the pore it swims freely until it becomes trapped again and this is termed as hopping. We can model the pores as individual microdomains and apply periodic boundary conditions to determine its diffusive rate through the domain patch. Using this diffusion rate we can model bacteria swimming over longer length scales where they encounter a microdomain of several pores within which they have this diffusion rate.

#### 2) Bacteria Clustering
It has been observed that some bacteria will cluster to swim faster. Their mobility relative to the cluster would be limited due to the presence of the other bacteria and so the hopping rates in the cluster would be slower, but the microdomain of the cluster would be translating with time and so we would need to alter the subvolume KMC method to account for this and we could also consider allowing for the size and shape of the nanodomain to change depending on lattice occupancy.

## References

1. Notes on Emerin Protein Diffusion

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

[Back To The Top](#PHYS516FINAL)
