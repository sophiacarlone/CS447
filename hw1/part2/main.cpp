#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <time.h>
#include <vector>

using namespace std;

// swap with no temp
#define swap(a,b)	((a)^=(b), (b)^=(a), (a)^=(b))

// prototypes of sorts
void bsort(int array[], int size);
void msort(int array[], int size);
void quicksort(int array[], int size, int pivot);
void msort(int array[], int low, int high);
void my_qsort(int array[], int size, int pivot);
void ssort(int array[], int size);
void merge(int array[], int low, int mid, int high);
void isort(int array[], int size);

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

		cout << size << " " << endl;

		show(test_array, size);

		int array[size];

		//testing bubble sort
		cost = 0;
		copy(test_array, array, size); //so that we can copy test_array again so it will always be the same  unsorted array
		bsort(array, size);
		is_sorted(array, size);
		cout << "bubble sort cost: " << cost << " " << endl;

		//do something for the other sorts
		cost = 0;
		copy(test_array, array, size);
		isort(array, size);
		is_sorted(array, size);
		cout << "insertion sort cost: " << cost << " " << endl;
		
		cost = 0;
		copy(test_array, array, size);
		ssort(array, size);
		is_sorted(array, size);
		cout << "selection sort cost: " << cost << " " << endl;

		cost = 0;
		copy(test_array, array, size);
		msort(array, size);
		is_sorted(array, size);
		cout << "merge sort cost: " << cost << " " << endl;

		cost = 0;
		copy(test_array, array, size);
		quicksort(array, size, 0);
		is_sorted(array, size);
		cout << "quicksort with fixed pivot cost: " << cost << " " << endl;

		cost = 0;
		copy(test_array, array, size);
		int pivot;
		select(array, size, size/2, pivot);
		my_qsort(array, size, pivot);
		is_sorted(array, size);
		cout << "quicksort with median pivot cost: " << cost << " " << endl;


		cout << endl;
		cost = 0;
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
	/*
	for(int i = size-1; i > 0; i--){
		for(int j = 0; j < i; j++){
			cost++; //TODO: make sure this is defined and used
			if(array[j] < array[j-1]){
				swap(array[j], array[j-1]);
			}
			else break;
		}
	}break*/    

    	for (int i = 0; i < size - 1; i++){
        	for (int j = 0; j < size - i - 1; j++){
			cost++;
                	if (array[j] > array[j + 1])
                        	swap(array[j], array[j + 1]);
		}
	}
}


//insertion sort
void isort(int array[], int size){
	if(size == 1) return;
	for(int i = 1; i < size; i++){
		for(int j = i; j > 0; j--){
			cost++;
			if(array[j] < array[j-1]) swap(array[j], array[j-1]);
			else break;
		}
	}
}

//merge sort
void msort(int array[], int size){
	msort(array, 0, size-1);
}

//merge sort helper
void msort(int array[], int low, int high){
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

	int left = low; //start
	int right = mid+1;

	int index = 0;
	while(left <= mid && right <= high){
		cost++;
		if(array[left] < array[right]){
			temp[index++] = array[left++];
		}
		else temp[index++] = array[right++];
	}
	while(left <= mid){
		temp[index++] = array[left++];
	}
	while(right <= high){
		temp[index++] = array[right++];
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
void my_qsort(int array[], int size, int pivot){
	if(size <= 1) return;
	if(size <= 2){
		cost++;
		if(array[0] > array[1]){
			swap(array[0], array[1]);
		}
		return;
	}

	//chose pivot
	//int pivot; 
	select(array, size, size/2, pivot);//change this to the select(k)
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
	my_qsort(array, left_v.size(), pivot);
	my_qsort(array+left_v.size()+1, right_v.size(), pivot);

}


//quicksort with fixed pivot (position 0)
void quicksort(int array[], int size, int pivot_index){
	if(size <= 1) return;
	if(size == 2){
		cost++;
		if(array[0] > array[1]){
			swap(array[0], array[1]);
		}
		return;
	}
	else{	
		cout << "pivot index: " << pivot_index << endl;
		int pivot = array[pivot_index];
		swap(array[pivot_index], array[size-1]);
		vector<int> left, right; //we are doing it anyways. Could make an array
		for(int i = 0; i < size-1; i ++){
			cost++;
			if(array[i] < pivot)left.push_back(array[i]);
			else right.push_back(array[i]);
		}

		//setting up array
		int ptr = 0;
		for(int i = 0; i < left.size(); i++) array[ptr++] = left[i];
		array[ptr++] = pivot;
		for(int i = 0; i < right.size(); i++) array[ptr++] = right[i];

		cout << "Sizes - left: " << left.size() << " right: " << right.size() << endl;

		quicksort(array, left.size(), 0);
		quicksort(array, right.size(), left.size());
		show(array, size);
	}
}


//find kth smallest element in the array
void select(int array[], int size, int K, int &answer){
	if(size < 5){
		assert(0 <= K && K < 5);
		bsort(array, size);
		answer = array[K];
		return;
	}
	
	//blocking 5
	for(int i = 0; i + 5 <= size; i = i+5) bsort(array+i, 5);

	//array of medians
	int median_num = size/5;
	int medians[median_num];

	for(int i = 0; i < median_num; i++) medians[i] = array[i+2]; //hmmm? seems like its just filling it up

	int pivot;
	select(medians, median_num, median_num/2, pivot);

	int index = 0;
	for(int i = 0; i < size; i++){
		if(array[i] == pivot){
			index = i;
			break;
		}
	}

	swap(array[index], array[size-1]); //why put it at the end?

	vector<int> left, right;

	for(int i = 0; i < size - 1; i++){
		cost++;
		if(array[i] <= pivot) left.push_back(array[i]);
		else right.push_back(array[i]);
	}

	int left_size = left.size();
	int right_size = right.size();

	if(K < left_size){
		int left_array[left_size];
		for(int i=0; i < left_size; i++) left_array[i] = left[i];
		select(left_array, left_size, K, answer);
	}
	else if(K == left_size) answer = pivot;
	else{
		int right_array[right_size];
		for(int i=0; i < right_size; i++) right_array[i] = right[i];
		select(right_array, right_size, K-(left_size+1), answer);
	}
}

	











