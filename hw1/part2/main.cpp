#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <time.h>

using namespace std;

// swap with no temp
#define swap(a,b)	((a)^=(b), (b)^=(a), (a)^=(b))

// prototypes of sorts
void bsort(int array[], int size);
//void qsort(int array[], int size, int (*choose_pivot)(int [], int));

// median finding (for quicksort)
void select(int array[], int size, int K, int &answer);

// helpers
void show(int array[], int size);
void copy(int src[], int dest[], int size);
void shuffle(int array[], int size);
void is_sorted(int array[], int size);

// global cost variable
int cost;

main(int argc, char* argv[]){
	assert(argc > 1);

	//get size
	int total_size = atoi(argv[1]);

	for(int size = 1; size < total_size; size++){
		//allocate array
		int test_array[size];
		for (int i = 0; i < size; i++){
			test_array[i] = i;
		}
		shuffle(test_array, size);

		cout << size << " ";

		int array[size];

		//testing bubble sort
		cost = 0;
		copy(test_array, array, size);
		bsort(array, size);
		is_sorted(array, size);
		cout << cost << " ";

		//do something for the other sorts
		

		cout << endl;
	}
}

// shuffle array uniformly at random
void shuffle(int array[], int size)
{
	int index;
	srand(time(0));
	for (int i=size-1; i>0; i--) {
		index = rand() % i;
		swap(array[i], array[index]);
	}
}

// show array
void show(int array[], int size)
{
	for (int i=0; i<size; i++) {
		cerr << array[i] << " ";
	}
	cerr << endl;
}

// test if array is sorted
void is_sorted(int array[], int size)
{
	for (int i=0; i<size-1; i++) {
		assert(array[i] <= array[i+1]);
	}
}

// copy array
void copy(int src[], int dest[], int size)
{
	for (int i=0; i<size; i++) {
		dest[i] = src[i];
	}
}
