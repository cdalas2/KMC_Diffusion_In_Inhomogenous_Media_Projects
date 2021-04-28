# PHYS516FINAL
<img src="InhomogeneousSchematic.png " width="600" height="400">

> Applying a kinetic monte carlo (KMC) method, for predicting the trajectories of freely diffusing particles in heterogeneous media [1,2], to investigate several problems in biophysics.

---

### Table of Contents
- [Subvolume Kinetic Monte Carlo](#subvolume-kinetic-monte-carlo)
- [Software And Installation](#software-and-installation)
- [How To Compile And Run It](#how-to-compile-and-run-it)
- [1. Protein Clustering](#1-protein-clustering)
- [2. Bacteria Hopping And Trapping](#2-bacteria-hopping-and-trapping)
- [3. How Did The Bacteria Cross The Road?](#3-how-did-the-bacteria-cross-the-road?)
- [Authors Info](#authors-info)

---

## Subvolume Kinetic Monte Carlo
We use the stochastic lattice model for particle diffusion in an inhomogeneous media [1] and perform subvolume KMC simulations [2] for our numerical calculations of the emerine monomer protein concentration trapped in the nanodomain with time in the steady state of the system.

#### Simulation steps
1. Domain patch is divided into *K* lattice cells.
2. Assign lattice info: System start state is *M* particles uniformly distributed along all cells; so *N=M/K* particles in each cell.
                        Each lattice cell is assigned a wait time between hops, *&tau;*, depending on its domain type.
                        Calculate transition rates *W(**N**,&tau;)* of each lattice cell.
                        Assign event times to each lattice cell using random numbers and the transition rates. Only one particle 
                        hop is simulated at each iteration and so the system of particles is evolved 1 hop at a time.
3. Sort lattice cells by their event time in a binary min heap. 
4. Pick the lattice cell at the top of the minheap for the particle to hop out of.
5. Randomly pick one of the nearest neighbors of this lattice cell, for the particle to hop into.
6. Update lattice info of lattice cells involved in the particle exchange.
7. Calculate new event times using random numbers for the lattice cells involved.
8. Re-sort the binary heap if necessary.
9. Repeat steps 4-8 for subsequent iterations until desired iteration or time limit is reached.

#### References
[1] Li, Y., Kahraman, O., & Haselwandter, C. A. (2017). Distribution of randomly diffusing particles in inhomogeneous media. Physical Review E, 96(3). https://doi.org/10.1103/physreve.96.032139

[2] Elf, J., Doncic, A., & Ehrenberg, M. (2003). Mesoscopic reaction-diffusion in intracellular signaling. In S. M. Bezrukov, H. Frauenfelder, & F. Moss (Eds.), Fluctuations and Noise in Biological, Biophysical, and Biomedical Systems. SPIE. https://doi.org/10.1117/12.497009


[Back To The Top](#PHYS516FINAL)

---

## Software And Installation
#### Software
The source code file KMC.c is written in C. There is a header file minHeap.h with heap functions used in KMC.c.

#### Installation
Download github repo. This will contain the necessary make file and source code files for build and compilation of the C code.


[Back To The Top](#PHYS516FINAL)

---

## How To Compile And Run It
On a terminal one can compile the source code file KMC.c by a make file provided to run a simulation. Then one can run the simulation by executing the executable generated, KMC. This will print the result to the terminal. In practice, we redirect the output to an output file KMC.out to save the data run which can then be plotted in an external plotter. We used MATLAB to plot the lattice cell schematic, the data run, and to edit the plot aesthetically. Our MATLAB mfile for reading in the data and plotting is included in the repository.

$ make

$ ./KMC > KMC.out


[Back To The Top](#PHYS516FINAL)

---

## 1. Protein Clustering
#### Description
We will look at the phenomenon of monomer emerin proteins freely diffusing through an inhomogenous nuclear membrane surface where the heterogeneity is due to the clustering of the emerin protein in the form of nanodomains with spacially different diffusion rates. We wish to track the trajectories of the emerin proteins. The motion of the emerin proteins is governed by diffusion through the membrane lipids. Within the nanodomain, the diffusion coefficient is about an order of magnitude slower than that outside of it, due to the clustering of emerin proteins there. PROJECT NOTES--->
<img src="KMC_ProjectNotes.pdf ">


#### Results
<img src="Lattice.png " width="450" height="400"><img src="KMC_freeDiffusion.png " width="550" height="400">

#### References
[3] Fernandez, A., Bautista, M. & Pinaud, F. Emerin oligomerization and nucleoskeletal coupling at the nuclear envelope regulate nuclear mechanics against stress. Submitted (2021). Available online at https://www.biorxiv.org/content/10.1101/2021.02.12.429834v2


[Back To The Top](#PHYS516FINAL)

---

## 2. Bacteria Hopping And Trapping
#### Description
Many bacteria swim in the form of a random walk in order to sample an area and build a gradient towards food or towards (away from) a specific chemical. Sometimes these bacteria can encounter media that limits their mobility, such as when traveling across a porous surface or into a fluid domain of a different viscosity. When the bacteria is in a pore it is described as being trapped. When the bacteria finds a way out of the pore it swims freely until it becomes trapped again and this is termed as hopping. We can model the pores as individual microdomains and apply periodic boundary conditions to determine its diffusive rate through the domain patch. Using this diffusion rate we can model bacteria swimming over longer length scales where they encounter a microdomain of several pores within which they have this diffusion rate.

#### Results
IN PROGRESS

#### References
[4] Bhattacharjee, T., & Datta, S. S. (2019). Bacterial hopping and trapping in porous media. Nature Communications, 10(1). https://doi.org/10.1038/s41467-019-10115-1

[5] Perez, L. J., Bhattacharjee, T., Datta, S. S., Parashar, R., & Sund, N. L. (2021). Impact of confined geometries on hopping and trapping of motile bacteria in porous media. Physical Review E, 103(1). https://doi.org/10.1103/physreve.103.012611

[6] Bhattacharjee, T., Amchin, D. B., Ott, J. A., Kratz, F., & Datta, S. S. (2020). Chemotactic Migration of Bacteria in Porous Media. Cold Spring Harbor Laboratory. https://doi.org/10.1101/2020.08.10.244731

[7] https://www.youtube.com/watch?v=JaxT-rZpte0

[8] https://www.youtube.com/watch?v=pjoojqw877A


[Back To The Top](#PHYS516FINAL)

---

## 3. How Did The Bacteria Cross The Road?
#### Description
It has been observed that some bacteria will cluster to swim faster. We can model a periodic highway of bacteria clusters and bacteria diffusing in the middle of this highway. The clusters would be modeled as microdomains that translate in time. In these moving microdomains, the mobility of the bacteria relative to the microdomain would be limited due to the clustering of bacteria and so the hopping rates in the microdomains would be slower than outside of them. So, if a bacteria hops into a microdomain, it would be essentially carried off by the microdomain and deposited into another domain patch after a time. Then, the bacteria would swim freely until another cluster picks it up again.

#### Results
NEED MORE BACKGROUND RESEARCH

#### References
NEED MORE BACKGROUND RESEARCH

[Back To The Top](#PHYS516FINAL)

---

## Authors Info
- LinkedIn - [Carlos Alas LI](https://www.linkedin.com/in/carlos-alas-6a4643160/)
- ResearchGate - [Carlos Alas RG](https://www.researchgate.net/profile/Carlos_Alas3)
- Trinh Lan Hoa


[Back To The Top](#PHYS516FINAL)
