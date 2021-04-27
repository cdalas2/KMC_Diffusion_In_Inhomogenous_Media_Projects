# PHYS516FINAL
<img src="InhomogeneousSchematic.png " width="600" height="400">

> A kinetic monte carlo (KMC) method for predicting the trajectories of freely diffusing particles in heterogeneous media applied to several problems in biophysics

---

### Table of Contents

- [Subvolume Kinetic Monte Carlo](#subvolume-kinetic-monte-carlo)
- [1. Protein Clustering](#1-protein-clustering)
- [2. Bacteria Hopping And Trapping](#2-bacteria-hopping-and-trapping)
- [3. Bacteria Clustering](#3-bacteria-clustering)
- [Software And Installation](#software-and-installation)
- [How To Compile And Run It](#how-to-compile-and-run-it)
- [Authors Info](#authors-info)

---

## Subvolume Kinetic Monte Carlo

We use the stochastic lattice model and perform subvolume KMC simulations for our numerical calculation as described in the reference paper {CITATION NEEDED HERE}.
1. Domain patch is divided into &K; cells.
2. System start state is M particles uniformly distributed along all cells; so 1 particle in each cell.
3. Calculate transition rates W(N,&tau;) of each lattice cell.
4. Assign event times to each lattice cell using random numbers and the transition rates. Only one particle 
  hop is simulated at each iteration and so the system of particles is evolved 1 hop at a time.
5. Sort lattice cells by their event time in a binary min heap.
6. 1st iteration will occur in the binary tree root node lattice cell of this heap.
7. Randomly pick one of the nearest neighbors of this lattice cell, for the particle to hop into.
8. Update lattice particle occupancy numbers and the transition rates of the lattice cells involved.
9. Calculate new event times using random numbers for the lattice cells involved.
10. Re-sort the binary heap if necessary.
11. Repeat 6-10 for subsequent iterations until desired iteration of time limit is reached.

#### References

1. Li, Y., Kahraman, O., & Haselwandter, C. A. (2017). Distribution of randomly diffusing particles in inhomogeneous media. Physical Review E, 96(3). https://doi.org/10.1103/physreve.96.032139

2. Elf, J., Doncic, A., & Ehrenberg, M. (2003). Mesoscopic reaction-diffusion in intracellular signaling. In S. M. Bezrukov, H. Frauenfelder, & F. Moss (Eds.), Fluctuations and Noise in Biological, Biophysical, and Biomedical Systems. SPIE. https://doi.org/10.1117/12.497009


[Back To The Top](#PHYS516FINAL)

---

## 1. Protein Clustering

#### Description
We will look at the phenomenon of monomer emerin proteins freely diffusing through an inhomogenous nuclear membrane surface where the heterogeneity is due to the clustering of the emerin protein in the form of nanodomains with spacially different diffusion rates. We wish to track the trajectories of the emerin proteins. The motion of the emerin proteins is governed by diffusion through the membrane lipids. Within the nanodomain, the diffusion coefficient is about an order of magnitude slower than that outside of it, due to the clustering of emerin proteins there. PROJECT NOTES--->
<img src="KMC_ProjectNotes.pdf ">


#### Results
<img src="Lattice.png " width="450" height="400"><img src="KMC_freeDiffusion.png " width="550" height="400">

#### References

1. Fernandez, A., Bautista, M. & Pinaud, F. Emerin oligomerization and nucleoskeletal coupling at the nuclear envelope regulate nuclear mechanics against stress. Submitted (2021). Available online at https://www.biorxiv.org/content/10.1101/2021.02.12.429834v2

2. F. Johansson. Arb: efficient arbitrary-precision midpoint-radius interval arithmetic. IEEE Transactions on Computers, 66:1281-1292, 2017.


[Back To The Top](#PHYS516FINAL)

---

## 2. Bacteria Hopping And Trapping

#### Description
Many bacteria swim in the form of a random walk in order to sample an area and build a gradient towards food or towards (away from) a specific chemical. Sometimes these bacteria can encounter media that limits their mobility, such as when traveling across a porous surface or into a fluid domain of a different viscosity. When the bacteria is in a pore it is described as being trapped. When the bacteria finds a way out of the pore it swims freely until it becomes trapped again and this is termed as hopping. We can model the pores as individual microdomains and apply periodic boundary conditions to determine its diffusive rate through the domain patch. Using this diffusion rate we can model bacteria swimming over longer length scales where they encounter a microdomain of several pores within which they have this diffusion rate.

#### Results
IN PROGRESS

#### References

1. Bhattacharjee, T., & Datta, S. S. (2019). Bacterial hopping and trapping in porous media. Nature Communications, 10(1). https://doi.org/10.1038/s41467-019-10115-1

2. Perez, L. J., Bhattacharjee, T., Datta, S. S., Parashar, R., & Sund, N. L. (2021). Impact of confined geometries on hopping and trapping of motile bacteria in porous media. Physical Review E, 103(1). https://doi.org/10.1103/physreve.103.012611

3. https://www.youtube.com/watch?v=JaxT-rZpte0

4. https://www.youtube.com/watch?v=pjoojqw877A


[Back To The Top](#PHYS516FINAL)

---

## 3. Bacteria Clustering

#### Description
It has been observed that some bacteria will cluster to swim faster. Their mobility relative to the cluster would be limited due to the presence of the other bacteria and so the hopping rates in the cluster would be slower, but the microdomain of the cluster would be translating with time and so we would need to alter the subvolume KMC method to account for this and we could also consider allowing for the size and shape of the nanodomain to change depending on lattice occupancy.

#### Results
NEED MORE BACKGROUND RESEARCH

#### References

1. Notes on Emerin Protein Diffusion

2. F. Johansson. Arb: efficient arbitrary-precision midpoint-radius interval arithmetic. IEEE Transactions on Computers, 66:1281-1292, 2017.


[Back To The Top](#PHYS516FINAL)

---

## Software And Installation

Download github repo. This will contain the necessary make file and source code files for build and compilation of C code.

[Back To The Top](#PHYS516FINAL)

---

## How To Compile And Run It

On a terminal one can compile a simulation by a make file provided. Then one can run the simulation by executing the executable generated, KMC. This will print the result to the terminal or command prompt. In practice, we redirect the output to an output file to save the data run.

$ make

$ ./KMC > KMC.out

[Back To The Top](#PHYS516FINAL)

---

## Authors Info

- LinkedIn - [Carlos Alas LI](https://www.linkedin.com/in/carlos-alas-6a4643160/)
- ResearchGate - [Carlos Alas RG](https://www.researchgate.net/profile/Carlos_Alas3)
- Trinh Lan Hoa

[Back To The Top](#PHYS516FINAL)
