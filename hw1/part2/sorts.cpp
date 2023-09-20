#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

#define swap(a,b)	((a)^=(b), (b)^=(a), (a)^=(b))

// prototypes
void bsort(int array[], int size);
void select(int array[], int size, int K, int &answer);

// the notorious bubble sort
void bsort(int array[], int size)
{
    for (int i=size-1; i>0; i--) {
        for (int j=0; j<i; j++) {
			cost++;
            if (array[j] > array[j+1]) {
                swap(array[j], array[j+1]);
            }
        }
    }
}

// search the Kth smallest element
void select(int array[], int size, int K, int &answer)
{
 	// FILL-IN
}
