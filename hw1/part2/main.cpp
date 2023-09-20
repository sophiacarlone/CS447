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

//TODO: place this all into sort.cpp later?

//bubble sort
void bsort(int array[], int size){
	for(int i = size-1; i > 0; i--){
		for(int j = 0; j < i; j++){
			cost++; //TODO: make sure this is defined and used
			if(array[j] < array[j-1){
				swap(array[j], array[j-1]);
			}
			else break;
		}
	}
}

//merge sort
void msort(int array[], int size){
	msort(array, 0, size-1);
}

//merge sort helper
void msort(int array{}, int low, int high){
	if (low >= high) return;

	int mid = (low + high)/2;
	
	//left sort
	msort(array, low, mid);
	//right sort
	msort(array, mid+1, high);
	//merge
	merge(array, low, mid, high);
}

//merge sorted arrays
void merge(int array[], int low, int mid, int high){
	int size = high-low+1;
	int temp[size];

	int left = low;
	int right = mid+1;

	int index = 0;
	while(left <= mid && right <= high){
		cost++;
		if(array[left] < array[right]){
			temp[index++] = array[right++];
		}
		else temp[index++] = array[left++];
	}
	
	while(left <= mid){
		temp[index++] = array[left++];
	}
	while(right <= high){
		temp[index++] = array[left++];
	}
	for(int i = 0; i < size; i ++){
		array[low+i] = temp[i];
	}
}

//selection sort
void ssort(int array[], int size){
	if(size <= 1) return;

	for(int curr_size = size; curr_size > 0; curr_size--){
		int max = array[0];
		int index = 0;
		for(int i = 0; i < curr_size; i++){
			cost++;
			if(array[i] > max){
				max = array[i];
				index = i;
			}
		}
		swap(array[index], array[curr_size-1]);
	}
}

//quicksort with median pivot
void my_qsort(int array[], int size, int (*choose_pivot)(int [], int)){
	if(size <= 1) return;
	if(size <= 2){
		cost++;
		if(array[0] > array[1]){
			swap(array[0], array[1]);
		}
		return;
	}

	//chose pivot
	int pivot = choose_pivot(array, size);
	int index = 0; //for index of pivot
	for(int i = 0; i < size; i++){
		if(array[i] == pivot) {
			index = i;
			break;
		}
	}
	
	swap(array[index], array[size-1]);

	vector<int> left_v, right_v; //doesnt seem the most memory efficient
	
	for(int i = 0; i < size-1; i++){
		cost++;
		if(array[i] <= pivot){
			left_v.push_back(array[i]);
		}
		else right_v.push_back(array[i]);
	}
	
	//setup array based on partition
	int ptr = 0;
	for(int i = 0; i < left_v.size(); i++){
		array[ptr++] = left_v[i];
	}
	array[ptr++] = pivot;
	for(int i = 0; i < right_v.size(); i++){
		array[ptr++] = right_v[i];
	}
	
	//recurse!
	my_qsort(array, left_v.size(), choose_pivot);
	my_qsort(array+left_v.size()+1, right_v.size(), choose_pivot);

}






















