# PHYS516FINAL
<img src="Lattice.png " width="550" height="500">

> A kinetic monte carlo (KMC) method for predicting the trajectories of freely diffusing particles in heterogeneous media applied to several problems in biophysics

---

### Table of Contents

- [Problems In Biophysics](#problems-in-biophysics)
- [Stochastic Lattice Model](#stochastic-lattice-model)
- [Subvolume Kinetic Monte Carlo](#subvolume-kinetic-monte-carlo)
- [Software And Installation](#software-and-installation)
- [How To Compile And Run It](#how-to-compile-and-run-it)
- [References](#references)
- [Author Info](#author-info)

---

## Problems In Biophysics

#### 1) Emerin proteins
We will look at the phenomenon of monomer emerin proteins freely diffusing through an inhomogenous nuclear membrane surface where the heterogeneity is due to the clustering of the emerin protein in the form of nanodomains with spacially different diffusion rates. Our system will consist of M=1600 total monomer emerin proteins. We wish to track the trajectories of the emerin proteins. The motion of the emerin proteins is governed by diffusion through the membrane lipids. Within the nanodomain, the diffusion coefficient is about an order of magnitude slower (D_{in} = 250 nm^{2}/s) than that outside of it (D_{out} = 3500 nm^{2}/s); the diffusion rate is slower in the nanodomain due to the clustering of emerin proteins there. 

#### 2) Bacteria hopping and trapping
Many bacteria swim in the form of a random walk in order to sample an area and build a gradient towards food or towards (away from) a specific chemical. Sometimes these bacteria can encounter media that limits their mobility, such as when traveling across a porous surface or into a fluid domain of a different viscosity. When the bacteria is in a pore it is described as being trapped. When the bacteria finds a way out of the pore it swims freely until it becomes trapped again and this is termed as hopping. We can model the pores as individual microdomains and apply periodic boundary conditions to determine its diffusive rate through the domain patch. Using this diffusion rate we can model bacteria swimming over longer length scales where they encounter a microdomain of several pores within which they have this diffusion rate.

#### 3) Bacteria Clustering
It has been observed that some bacteria will cluster to swim faster. Their mobility relative to the cluster would be limited due to the presence of the other bacteria and so the hopping rates in the cluster would be slower, but the microdomain of the cluster would be translating with time and so we would need to alter the subvolume KMC method to account for this and we could also consider allowing for the size and shape of the nanodomain to change depending on lattice occupancy.

[Back To The Top](#PHYS516FINAL)

---

## Stochastic Lattice Model

We use only open-source software, so our approach is easily accessible to anyone with a laptop or desktop computer.

- C++
- Arblib library (version 2.17 or newer)
- Carlos_Membrane_Project
- OpenMP
- OpenMPI (if you want to do calculations for multiple protein systems)
- Paraview

[Back To The Top](#PHYS516FINAL)

---

## Subvolume Kinetic Monte Carlo

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

## Software And Installation

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

[Back To The Top](#PHYS516FINAL)
