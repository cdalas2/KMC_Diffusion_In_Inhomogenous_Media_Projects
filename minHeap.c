#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "minHeap.h"

int main() {
    // int n = 10;
    // int a[MAX_SIZE];
    // double b[MAX_SIZE];

    // for(int i=0; i<n; i++){
    //     a[i] = i+1;
    // }
    // b[0] = 10.0; b[1] = 12.0; b[2] = 9.0;  b[3] = 78.0; b[4] = 33.0; 
    // b[5] = 21.0; b[6] = 35.0; b[7] = 29.0; b[8] = 5.0;  b[9] = 66.0;
    // for(int i=10; i<MAX_SIZE; i++){
    //     b[i] = INFINITY;
    // }
    // print_heap(a, b, n);
    // build_min_heap(a, b, n);
    // print_heap(a, b, n);
    // insert(a, b, 55.0, &n);
    // print_heap(a, b, n);
    // insert(a, b, 56.0, &n);
    // print_heap(a, b, n);
    // insert(a, b, 57.0, &n);
    // print_heap(a, b, n);
    // insert(a, b, 58.0, &n);
    // print_heap(a, b, n);
    // insert(a, b, 100.0, &n);
    // print_heap(a, b, n);
    //srand(time(NULL));
    double num1 = -log((double)rand() / (double)RAND_MAX);
    double num2 = -log((double)rand() / (double)RAND_MAX);
    printf("%f\t%f\n",num1,num2);
    return 0;
}