![USCPHYS](https://user-images.githubusercontent.com/62254347/117349003-bcf17900-ae5f-11eb-9f3b-d0ceb8e59e50.gif)
>I made this gif using our SKMC code, where the letters are subdomains assigned a slower diffusion rate.

# Kinetic Monte Carlo methods for diffusion in various inhomogeneous media
> I applied kinetic monte carlo (KMC) methods, for predicting the trajectories of freely diffusing particles in various heterogeneous media [1,2], to investigate several scenarios in biophysics. 

https://user-images.githubusercontent.com/62254347/117113593-891f3200-ad3f-11eb-8b3e-be868e8ae310.mp4
> This video is of a non-interacting bacteria population diffusing through pores of characteristic size 3.24 &mu;m with measurement taken from [4], where I initialized the simulation with the entire population of bacteria in one cell, as to simulate the population emerging from a pipette or syringe; periodic boundary conditions are enforced at the boundaries of the domain volume. The simulated time was 20s, but the video is slowed to 99s.

---

### Table of Contents
- [1. Protein Clustering](#1-protein-clustering)
  - [Subvolume Kinetic Monte Carlo](#subvolume-kinetic-monte-carlo)
    - [SKMC Simulation Steps](#skmc-simulation-steps)
  - [Results Of Protein Clustering Simulations](#results-of-protein-clustering-simulations)
  - [References For Protein Clustering Scenario](#references-for-protein-clustering-scenario)
- [2. Bacteria Hopping And Trapping](#2-bacteria-hopping-and-trapping)
  - [Subvolume Kinetic Monte Carlo With Distributed Hop Length And Trapped Time](#subvolume-kinetic-monte-carlo-with-distributed-hop-length-and-trapped-time)
    - [SKMCHT Simulation Steps](#skmcht-simulation-steps)
  - [Results of Bacteria Hopping And Trapping Simulations](#results-of-bacteria-hopping-and-trapping-simulations)
  - [References For Bacteria Hopping And Trapping Scenario](#references-for-bacteria-hopping-and-trapping-scenario)
- [3. Bacteria Bus Ride](#3-bacteria-bus-ride)
  - [Subvolume Kinetic Monte Carlo With Translating Microdomains](#subvolume-kinetic-monte-carlo-with-translating-microdomains)
    - [SKMCTM Simulation Steps](#skmctm-simulation-steps)
  - [Results of Bacteria Bus Ride Simulations](#results-of-bacteria-bus-ride-simulations)
  - [References For Bacteria Bus Ride Scenario](#references-for-bacteria-bus-ride-scenario)
- [Software And Installation](#software-and-installation)
  - [Software](#software)
  - [Installation](#installation)
- [How To Compile And Run It](#how-to-compile-and-run-it)
- [Authors Info](#authors-info)

---

[Back To The Top](#Kinetic-Monte-Carlo-methods-for-diffusion-in-various-inhomogeneous-media)

## 1. Protein Clustering
![sqrNano](https://user-images.githubusercontent.com/62254347/117357807-3db57280-ae6a-11eb-9da4-46301db5b705.gif)
>This gif is of the first 5 minutes, of our SKMC run of a square nanodomain as described in our project notes, condensed to 20 seconds.

I will look at the phenomenon of monomer emerin proteins freely diffusing through an inhomogenous nuclear membrane surface where the heterogeneity is due to the clustering of the emerin protein in the form of nanodomains with spacially different diffusion rates. I wish to track the trajectories of the emerin proteins. The motion of the emerin proteins is governed by diffusion through the membrane lipids. Within the nanodomain, the diffusion coefficient is about an order of magnitude slower than that outside of it, due to the clustering of emerin proteins there. PROJECT NOTES REMOVED SINCE THIS PROJECT WILL BE EXTENDED INTO A PUBLICATION RESEARCH PROJECT IN 2022.

### Subvolume Kinetic Monte Carlo
I use the stochastic lattice model for particle diffusion in an inhomogeneous media [1] and perform subvolume KMC simulations [2] for my numerical calculations of the emerin monomer protein concentration trapped in the nanodomain as a function of time. 

#### SKMC Simulation Steps
1. Domain patch is divided into *K* lattice cells.
2. Assign lattice info: System start state is *M* particles uniformly distributed along all cells; so *N=M/K* particles in each cell.
                        Each lattice cell is assigned an average wait time between hops, *&tau;*, depending on its domain type.
                        Calculate transition rates *W(**N**,&tau;)* of each lattice cell.
                        Sample event times from a Poisson distribution fitted to the mean hop time in each lattice cell using random 
                        numbers and the transition rates. Only one particle hop is simulated at each iteration and so the system of
                        particles is evolved 1 hop at a time.
3. Sort lattice cells by their event time in a binary min heap. 
4. Pick the lattice cell at the top of the minheap for the particle to hop out of.
5. Randomly pick one of the nearest neighbors of this lattice cell, for the particle to hop into.
6. Update lattice info of lattice cells involved in the particle exchange.
7. Sample new event times for the lattice cells involved.
8. Re-sort the binary heap if necessary.
9. Repeat steps 4-8 for subsequent iterations until desired iteration or time limit is reached.

### Results Of Protein Clustering Simulations
I used the lattice discretization of the domain and nanodomain shown in the figure on the left; the nanodomain is highlighted in red.
I evolved the system of proteins for about 4 hours at which it was at a steady state with a nanodomain protein concentration of about 53%. Averaging the protein concentration over the 4 hours gave a mean concentration that differed less than 1% from the analytical solution for this situation; shown in the figure on the right.
It is also interesting that this simple model which could be characterized by a different diffusion rate in the nanodomain suggests that protein clustering emerges from a change in diffusion rates in part of the domain. Diffusion rates can be varied by means of a mechanical stress on the membrane and so proteins may respond to mechanical stimuli by clustering due to changes in the rates of diffusion by the mechanical stimuli.

<img src="Lattice.png " width="425" height="375"><img src="KMC_freeDiffusion.png " width="525" height="375">

### References For Protein Clustering Scenario
[1] Li, Y., Kahraman, O., & Haselwandter, C. A. (2017). Distribution of randomly diffusing particles in inhomogeneous media. Physical Review E, 96(3). https://doi.org/10.1103/physreve.96.032139

[2] Elf, J., Doncic, A., & Ehrenberg, M. (2003). Mesoscopic reaction-diffusion in intracellular signaling. In S. M. Bezrukov, H. Frauenfelder, & F. Moss (Eds.), Fluctuations and Noise in Biological, Biophysical, and Biomedical Systems. SPIE. https://doi.org/10.1117/12.497009

[3] Fernandez, A., Bautista, M. & Pinaud, F. Emerin oligomerization and nucleoskeletal coupling at the nuclear envelope regulate nuclear mechanics against stress. Submitted (2021). Available online at https://www.biorxiv.org/content/10.1101/2021.02.12.429834v2


[Back To The Top](#Kinetic-Monte-Carlo-methods-for-diffusion-in-various-inhomogeneous-media)

---

## 2. Bacteria Hopping And Trapping
https://user-images.githubusercontent.com/62254347/116847393-47f01c00-ab9f-11eb-92a6-7ece68e53c37.mp4
> In this video, I show the random walk of a single bacteria through a pore space with pores of characteristic size 3.6 &mu;m and using measurments from [4]. Here I show its diffusion without periodic boundary conditions but in an infinite domain. The simulation time is 10-minutes, though the video, here, has been condensed to 27s.

https://user-images.githubusercontent.com/62254347/116849027-bbdff380-aba2-11eb-941d-144c1c617acd.mp4
>This video is the same simulation as the previous video, but with a black background and without the trajectory line.

Many bacteria swim in the form of a random walk in order to sample an area and build a gradient towards food or towards (away from) a specific chemical. These bacteria perform a two-state motion (run and tumble) that involves an alternation of a directed swim and a stop and reorientation of direction. Sometimes these bacteria can encounter media that severly limits their mobility, such as when traveling through a porous media. It has been observed [4] that instead of the run and tumble motion, a hopping and trapping motion is ensued by the bacteria to navigate the porous media. While swimming in a porous media, the bacteria get stuck between a pore and some of its neighboring pores. In this trapped time, the bacteria randomly re-orients its direction to find a way out. Once the bacteria find a way out it swims straight until it gets stuck again. Its swim length between traps are the hop lengths which are set by the solid matrix of the pore cluster. The trap times are longer than the hop times and so we model the motion as transitions between trapped states using a an alteration of the subvolume KMC method. PROJECT NOTES---> <img src="KMC_Bacteria_Hopping_And_Trapping.pdf ">

### Subvolume Kinetic Monte Carlo With Distributed Hop Length And Trapped Time
I use an alteration of the subvolume kinetic Monte Carlo [2] which samples the hop lengths and trapped times in addition to the event time.

#### SKMCHT Simulation Steps
1. Domain area/volume is divided into *K* lattice cells.
2. Assign lattice info: System start state is *M* particles distributed amongst the lattice cells. 
                        Each lattice cell is assigned a Poisson distribution randomly sampled trapped time between states, *&tau;*.
                        Calculate transition rates *W(**N**,&tau;)* of each lattice cell.
                        Assign sampled event times to each lattice cell using the transition rates (*t = 1/W*). Only one particle hop 
                        is simulated at each iteration and so the system of particles is evolved 1 hop at a time.
3. Sort lattice cells by their event time in a binary min heap. 
4. Pick the lattice cell at the top of the minheap for the particle to hop out of.
5. Randomly pick a direction for the particle to hop along by a uniform distribution.
6. Assign a Poisson distribution randomly sampled hop length for the particle to hop in the randomly chosen direction.
7. Update lattice info of lattice cells involved in the particle exchange.
8. Assign new event times using the new occupation numbers and new sampled trapped times for the lattice cells involved.
9. Re-sort the binary heap if necessary.
10. Repeat steps 4-9 for subsequent iterations until desired iteration or time limit is reached.

### Results Of Bacteria Hopping And Trapping Simulations
I ran 10-minute simulations of a single bacteria transitioning between trapped states in a domain volume. I ran the simulation 100000 times, averaging over the diffusion coefficient as a function of iterations; this is shown in the figure on the left. I compared my simulated diffusion coefficients averaged over 100000 iterations against the measured coefficients of [4] for pore distributions with characteristic pore sizes 3.6, 2.5, and 1.9 &mu;m in the figure on the right. I found that the measured diffusivities of the experiments in [4] are about (0.9+-0.1) times my simulated diffusivities averaged over 100000 10-minute iterations. The measured diffusivities in [4] are reported to the nearest 0.5 &mu;m^2/s and so our simulated values for pores of sizes 1.9 &mu;m and 2.5 &mu;m agree quite well for this level of precision in the measured values. My simulated diffusivity for pores of size 3.6 &mu;m is closer to 2.5 &mu;m^2/s than the reported measured value of about 2 &mu;m^2/s, which I attribute to the bacteria spending less time trapped and more time hopping. Since my model assumes the hopping time to be negligible, I always underestimate the transition times and so my simulated values always overestimate the measured diffusivities.

<img src="SKMCHT_DiffusionIters.png " width="500" height="375"><img src="SKMCHT_KMCvsEXP.png " width="500" height="375">


### References For Bacteria Hopping And Trapping Scenario
[4] Bhattacharjee, T., & Datta, S. S. (2019). Bacterial hopping and trapping in porous media. Nature Communications, 10(1). https://doi.org/10.1038/s41467-019-10115-1

[5] https://www.youtube.com/watch?v=JaxT-rZpte0

[6] https://www.youtube.com/watch?v=pjoojqw877A


[Back To The Top](#Kinetic-Monte-Carlo-methods-for-diffusion-in-various-inhomogeneous-media)

---

## 3. Bacteria Bus Ride
![BacteriaBusRide2D](https://user-images.githubusercontent.com/62254347/118174728-09026780-b3e4-11eb-987f-f3936eb19c82.gif)

It has been observed that some bacteria will cluster to swim faster. I can model a periodic highway of bacteria clusters and bacteria diffusing in the middle of this highway. The clusters would be modeled as microdomains that translate in time. In these moving microdomains, the mobility of the bacteria relative to the microdomain would be limited due to the clustering of bacteria and so the hopping rates in the microdomains would be slower than outside of them. So, if a bacteria hops into a microdomain, it would be essentially carried off by the microdomain and deposited into another domain patch after a time. Then, the bacteria would swim freely until another cluster picks it up again. Perhaps my model will yield the bacteria clustering phenomenon similar to the static nanodomain case of protein clustering.

### Subvolume Kinetic Monte Carlo With Translating Microdomains
I use an alteration of the subvolume kinetic Monte Carlo [2] which includes interval checks between iterations for a microdomain that translate at a constant velocity.

#### SKMCTM Simulation Steps
1. Domain volume is divided into *K* lattice cells.
2. Assign lattice info: System start state is *M* particles uniformly distributed along all cells; so *N=M/K* particles in each cell.
                        Each lattice cell is assigned an average wait time between hops, *&tau;*, depending on its domain type.
                        Calculate transition rates *W(**N**,&tau;)* of each lattice cell.
                        Sample event times for each lattice cell using random numbers and the transition rates.
3. Sort lattice cells by their event time in a binary min heap. 
4. The microdomain is of constant shape and translates at a constant 40 micrometers per second Eastward, always. 
   So we check if its time to translate the microdomain over by one lattice cell by comparing the next active cell's event time to the microdomain's next            translation event time.
5. If its time to translate the microdomain, we shift over the occupancy numbers of the lattice cells in the 
   microdomain over one lattice cells to the right and re-sample the event times of the lattice cells based on their new occupancy numbers and diffusion rates.      The min heap is re-sorted, if necessary, and step 4 is repeated.
6. If it is not time to translate the microdomain, we proceed as we would with a non-translating microdomain. We pick the lattice 
   cell at the top of the minheap for the particle to hop out of.
7. Randomly pick one of the nearest neighbors of this lattice cell, for the particle to hop into.
8. Update lattice info of lattice cells involved in the particle exchange.
9. Sample new event times for the lattice cells involved.
10. Re-sort the binary heap if necessary.
11. Repeat steps 4-10 for subsequent iterations until desired iteration or time limit is reached.

### Results Of Bacteria Bus Ride Simulations
<img src="SKMCTM3D_rho.png" width="575" height="400">

### References For Bacteria Bus Ride Scenario
[7] Mittal, N., Budrene, E. O., Brenner, M. P., & van Oudenaarden, A. (2003). Motility of Escherichia coli cells in clusters formed by chemotactic aggregation. Proceedings of the National Academy of Sciences, 100(23), 13259–13263. https://doi.org/10.1073/pnas.2233626100

[8] Darnton, N. C., Turner, L., Rojevsky, S., & Berg, H. C. (2010). Dynamics of Bacterial Swarming. Biophysical Journal, 98(10), 2082–2090.           https://doi.org/10.1016/j.bpj.2010.01.053

[9] Tung, C., Lin, C., Harvey, B., Fiore, A. G., Ardon, F., Wu, M., & Suarez, S. S. (2017). Fluid viscoelasticity promotes collective swimming of sperm. Scientific Reports, 7(1). https://doi.org/10.1038/s41598-017-03341-4



[Back To The Top](#Kinetic-Monte-Carlo-methods-for-diffusion-in-various-inhomogeneous-media)

---

## Software And Installation
### Software
The source code files are SKMC.c, SKMCHT2D.c, SKMCHT3D.c, SKMCTM2D.c, and SKMCTM3D.c. ***All of these source code files rely on the header file minHeap.h being in the same folder***.
1. **SKMC.c** runs simulations of proteins diffusing in a 2D domain with a nanodomain of a different diffusion rate. Periodic boundaries are imposed to simulate and infinite membrane. Direction at each step is sampled uniformly (up,down,left,right) and the hop times are sampled from a Poisson distribution fitted to the local hopping time scaled by the number of transition states. This file outputs the concentration of proteins in the nanodomain as a function of time.
2. **SKMCHT2D.c** runs simulations of bacteria hopping and trapping diffusion in a 2D domain. Direction at each step is sampled uniformly (up,down,left,right) and the hop lengths and trapped times are sampled from Poisson distributions. The trapped time Poisson distribution is fitted to its mean value scaled the number of transition states. The hop length Poisson distribution is fitted to its mean value. This file outputs the averaged diffusion coefficient as a function of the number of simulations used in its calculation.
3. **SKMCHT3D.c** runs simulations of bacteria hopping and trapping diffusion in a 3D domain. Direction at each step is sampled uniformly (North,South,West,East,Above,Below) and the hop lengths and trapped times are sampled from Poisson distributions. The trapped time Poisson distribution is fitted to its mean value scaled the number of transition states. The hop length Poisson distribution is fitted to its mean value. This file outputs the averaged diffusion coefficient as a function of the number of simulations used in its calculation.
4. **SKMCTM2D.c** runs simulations of particle diffusion in a 2D domain with a translating sub domain. Direction at each step is sampled uniformly (up,right,down,left) and the lattice event times are sampled from a Poisson distribution fitted to the mean hop time. Before each event, the event of subdomain's translation is checked for and carried out if it is time to do so. This file outputs the concentration of particles in the subdomain as a function of time.
5. **SKMCTM3D.c** runs simulations of particle diffusion in a 3D domain with a translating sub domain. Direction at each step is sampled uniformly (North,South,West,East,Above,Below) and the lattice event times are sampled from a Poisson distribution fitted to the mean hop time. Before each event, the event of subdomain's translation is checked for and carried out if it is time to do so. This file outputs the concentration of particles in the subdomain as a function of time.
6. **minHeap.h** holds binary minimum heap functions for sorting a double array into a binary minimum heap and using an additional interger array to keep track of their indexes. We use this to create a priority queue in our KMC simulations to tell us which lattice cell will have a state transition event next and at what time. The binary minimum heap functions are (a) parent node, (b) left child, (c) right child for finding the parent and children node of any node in the binary tree of the min heap, (d) heapify for downward percolation in sorting, (e) decrease key for upward percolation in sorting, (f) build a min heap for sorting a double type array into a min heap by using heapify recurringly, and other trivial functions for swapping numbers and printing out the minheap to the terminal.

### Installation
Download GitHub repo. This will contain the necessary make file and source code files for the simulations.


[Back To The Top](#Kinetic-Monte-Carlo-methods-for-diffusion-in-various-inhomogeneous-media)

---

## How To Compile And Run It
On a terminal one can compile the source code file SKMC.c by a make file provided to run a simulation. Then one can run the simulation by executing the executable generated, SKMC. This will print the result to the terminal. In practice, I redirect the output to an output file SKMC.o to save the data run which can then be plotted in an external plotter. We used MATLAB to plot the lattice cell schematic, the data run, and to edit the plot aesthetically. My MATLAB mfile for reading in the data and plotting is included in the repository. 

$ make

$ ./SKMC > SKMC.o

To run simulations from the other source code files, one simply needs to change out the prefix "SKMC" from in the make file to the name of the source code file simulation you want to build, compile, and run and the name of the executable will be the same as the source code file. 

[Back To The Top](#Kinetic-Monte-Carlo-methods-for-diffusion-in-various-inhomogeneous-media)

---

## Authors Info
- LinkedIn - [Carlos Alas LI](https://www.linkedin.com/in/carlos-alas-6a4643160/)
- ResearchGate - [Carlos Alas RG](https://www.researchgate.net/profile/Carlos_Alas3)


[Back To The Top](#Kinetic-Monte-Carlo-methods-for-diffusion-in-various-inhomogeneous-media)
