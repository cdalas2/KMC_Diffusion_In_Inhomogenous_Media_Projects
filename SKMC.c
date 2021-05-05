/*******************************************************************************
Subvolume KMC Simulations of freely diffusing monomer emerin proteins in
a domain with a nanodomain of a different diffusion rate due to the clustering
of the emerin proteins there

USAGE

%cc -O3 KMC.c -o KMC
%./KMC > KMC.out
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "minHeap.h"

#define SNAPSHOT_RATE 1 /* we take a snapshot after every SNAPSHOT_RATE events */
#define TOTAL_PROTEIN_NUM 1600 /* Total number of emerin monomer proteins */
#define NUM_CELLS_ONESIDE 40 /* number of lattice cells along one side of square system domain */
#define TOTAL_LATTICE_CELLS (NUM_CELLS_ONESIDE*NUM_CELLS_ONESIDE) /* Total number of lattice cells */
#define N0 (TOTAL_PROTEIN_NUM/TOTAL_LATTICE_CELLS) /* Initial number of proteins in each lattice */
#define D_IN 250.0 /* Diffusion coefficient inside nanodomain (nanometers^2/W) */
#define D_OUT 3500.0 /* Diffusion coefficient outside nanodomain (nanometers^2/W) */
#define A_IN 12100.0 /* Area of nanodomain (nm^2) */
#define NCPS 11 /* number of lattice cells per side of square nanodomain */
#define A (400.0*400.0) /* Total area of system domain (nm^2) */
#define A_OUT (A - A_IN) /* Area outside nanodomain (nm^2) */
#define LATTICE_CELL_LENGTH 10.0 /* lattice cell length (nm)*/
#define TAU_IN (LATTICE_CELL_LENGTH*LATTICE_CELL_LENGTH/D_IN) /* time between hops inside nanodomain (W) */
#define TAU_OUT (LATTICE_CELL_LENGTH*LATTICE_CELL_LENGTH/D_OUT) /* time between hops outside nanodomain (W) */
#define TIME_MAX 14500.0

int main() {
  /* directionID will hold lattice neighbor index protein hops into */
  /* lambda will hold the index of the lattice site index it hops out of */
  /* gamma will hold the index of the lattice site index it hops into */
  /* u1,u2,u3,u4 are to hold randoms numbers */
  int directionID, lambda, gamma, u2;
  double u1, u3, u4;

  /* Nin is for the number of proteins inside the nanodomain
     and Ntot is for the total number of proteins across 
     all lattice cells */
  int Nin = 0, Ntot = 0;

  /* tlambda will hold the sampled event time in lattice lambda */
  /* tgamma will hold the sampled event time in lattice gamma */
  double tlambda = 0.0, tgamma = 0.0;

  int N[TOTAL_LATTICE_CELLS]; /* number of emerin monomer proteins in each lattice cell */
  int nn[TOTAL_LATTICE_CELLS][4]; /* nearest neighbors of each lattice cell, we use 
                   periodic boundary conditions at system boundary */
  double W[TOTAL_LATTICE_CELLS]; /* transition rates (diffusion intensities) in each lattice cell */
  double t[TOTAL_LATTICE_CELLS]; /* next queued (sampled) event time in each lattice cell */
  double tau[TOTAL_LATTICE_CELLS]; /* time between hops in each lattice cell */
  int LCells2D[NUM_CELLS_ONESIDE+2][NUM_CELLS_ONESIDE+2]; /* indexes of each lattice cell with padding on top,
                           bottom, left, and right sides to account for the 
                           periodic boundary conditions */
  int Q[TOTAL_LATTICE_CELLS]; /* will hold indexes of the lattice cells organized by their 
               their order in the event queue */
  
  /* Assign the time between hops in each lattice cell.
     Our nanodomain is square with top left corner at
     lattice cell i = 23 + 20*NUM_CELLS_ONESIDE */
  for(int i=0; i<TOTAL_LATTICE_CELLS; i++){ /* First we will set all times to TAU_OUT */
    tau[i] = TAU_OUT;
    Q[i] = i; /* to be sorted by their order of event occurrence later */
  }
 
  for(int i=0; i<NCPS; i++){ /* Now we switch in hop times inside nanodomain */
      for(int j=(23+20*NUM_CELLS_ONESIDE); j<(23+20*NUM_CELLS_ONESIDE+NCPS); j++){
          tau[j + i*NUM_CELLS_ONESIDE] = TAU_IN;      
      }
  }
  
  /* filling indexes of lattice cells into an array 
     which is padded on all sides to reflect the
     periodic boundary conditions */
  for(int i=1; i<NUM_CELLS_ONESIDE+1; i++){
    for(int j=1; j<NUM_CELLS_ONESIDE+1; j++){
        LCells2D[i][j] = (i-1)*NUM_CELLS_ONESIDE + j-1;
    }
  }

  for(int j=1; j<NUM_CELLS_ONESIDE+1; j++){
      LCells2D[0][j] = j-1 + (NUM_CELLS_ONESIDE-1)*NUM_CELLS_ONESIDE;
      LCells2D[NUM_CELLS_ONESIDE+1][j] = j-1;
  }

  for(int i=1; i<NUM_CELLS_ONESIDE+1; i++){
      LCells2D[i][0] = LCells2D[i][NUM_CELLS_ONESIDE];
      LCells2D[i][NUM_CELLS_ONESIDE+1] = LCells2D[i][1];
  }

  /* fill corners with INFINITY since they are irrelevant */
  LCells2D[0][0] = INFINITY;
  LCells2D[0][NUM_CELLS_ONESIDE+1] = INFINITY;
  LCells2D[NUM_CELLS_ONESIDE+1][0] = INFINITY;
  LCells2D[NUM_CELLS_ONESIDE+1][NUM_CELLS_ONESIDE+1] = INFINITY;

  /* Here we fill in the neighbor list of each lattice cell */
  for(int i=0; i<NUM_CELLS_ONESIDE; i++){
    for(int j=0; j<NUM_CELLS_ONESIDE; j++){
        nn[i*NUM_CELLS_ONESIDE + j][0] = LCells2D[i][j+1]; /* up */
        nn[i*NUM_CELLS_ONESIDE + j][1] = LCells2D[i+1][j+2]; /* right */
        nn[i*NUM_CELLS_ONESIDE + j][2] = LCells2D[i+2][j+1]; /* down */
        nn[i*NUM_CELLS_ONESIDE + j][3] = LCells2D[i+1][j]; /* left */
    }
  }

  /* We initialize a uniform distribution of emerin monomer
     proteins over the lattice cells and calculate
     the transition rates for the subvolume KMC method. 
     We then assign a random event time sampled from the 
     probability distribution (master equation). We keep track
     of the total number of proteins Ntot to make sure its constant */
  srand(time(NULL));
  for(int i=0; i<TOTAL_LATTICE_CELLS; i++){
      N[i] =  N0;
      W[i] = (double)N[i]/tau[i]/4; 
      u1 = (double)rand() / RAND_MAX;
      t[i] = -log(u1) / W[i];
      Ntot = Ntot + N[i];
  }

  /* Now we sum up the number of proteins in the nanodomain
     and calculate the total number of proteins outside the
     nanodomain */
  for(int i=0; i<NCPS; i++) {
      for(int j=(23+20*NUM_CELLS_ONESIDE); j<(23+20*NUM_CELLS_ONESIDE+NCPS); j++){
          Nin = Nin + N[j + i*NUM_CELLS_ONESIDE];        
      }
  }

  build_min_heap(Q, t, TOTAL_LATTICE_CELLS); /* create priority queue as a binary min heap 
                              organized by the time of the event in each
                              lattice cell */
  int pt = 0; /* event id */
  while(t[0] <= TIME_MAX){ /* we will run the simulation for 4 hours */
    /* assign random integer to picture direction to hop in */
    u2 = rand();
    directionID = u2%4;

    /* grab the index of the lattice cell where the next event will occur */
    lambda = Q[0];
    /* grab the index of the lattice cell the protein hops into */
    gamma = nn[lambda][directionID];

    if(pt%SNAPSHOT_RATE == 0){ /* this is the snapshot conditional statement
                               where we print a snapshot of the system */
      /* we keep track of the concentration of proteins in the nanodomain
         Nin/Ntot as a function of simulation time t[0] */
      printf("%f\t%f\n",(double)Nin/Ntot,t[0]);
    }
    /* 1 protein hops out of lattice cell lambda */
    N[lambda] = N[lambda] - 1;
    /* update transition rate in lattice cell lambda */
    W[lambda] = (double)N[lambda]/tau[lambda]/4;
    /* save the current event time */
    tlambda = t[0];
    /* 1 protein hops into lattice cell gamma */
    N[gamma] = N[gamma] + 1;
    /* update transition rate in lattice cell gamma */
    W[gamma] = (double)N[gamma]/tau[gamma]/4;

    /* assign random number to calculate new event time in lattice cell lambda */
    u3 = (double)rand() / RAND_MAX;
    t[0] = tlambda - log(u3) / W[lambda];

    /* update order of the priority queue by percolating down the heap*/
    min_heapify(Q, t, 0, TOTAL_LATTICE_CELLS);

    /* search priority queue lattice cell gamma */
    for(int i=0; i<TOTAL_LATTICE_CELLS; i++){
      /* when lattice cell gamma is found in Q
         we update its event time */
      if(Q[i] != gamma){ 
      }
      else{
        /* save event time in lattice cell gamma for comparison */
        tgamma = t[i];
        /* assign random number to calculate new event time in lattice cell gamma */
        u4 = (double)rand() / RAND_MAX;
        t[i] = tlambda - log(u4)/W[gamma];
        /* if new event time is less than old event time
           we use decrease to percolate up the heap */
        if(t[i] < tgamma) {
          decrease_key(Q, t, i);
        }
        else if(t[i] > tgamma) {/* if new event time is greater than old event time
                                   we use heapify to percolate down the heap */
          min_heapify(Q, t, i, TOTAL_LATTICE_CELLS);
        }
        break; /* break out of for loop once lattice cell gamma is found
                  and priority queue is updated */
      }
    }

    /* recount the number of protein inside the nanodomain and in total */
    Nin = 0;
    Ntot = 0;
    for(int i=0; i<TOTAL_LATTICE_CELLS; i++){
      Ntot = Ntot + N[i];
    }
    for(int i=0; i<NCPS; i++){
      for(int j=(23+20*NUM_CELLS_ONESIDE); j<(23+20*NUM_CELLS_ONESIDE+NCPS); j++){
          Nin = Nin + N[j + i*NUM_CELLS_ONESIDE];        
      }
    } 
    pt = pt+1; /* increment event id */
  } /* end of while loop after TIME_MAX */
   printf("\n");
  
  return 0;
}
