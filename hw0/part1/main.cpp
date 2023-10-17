#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

// macro to swap pair of elements
#define swap(a,b)	((a) ^= (b), (b) ^= (a), (a) ^= (b))

// prototypes
void show_array( int [], int );
void init_array( int [], int );
void shuffle_array( int [], int );
void min_search( int [], int, int & );
void select_sort( int [], int );
int is_sorted( int [], int );
void max_search( int buffer[], int size, int &answer );
void min_search_recursion( int buffer[], int size, int &answer);
void max_search_recursion( int buffer[], int size, int &answer);
void MINMAX_loop(int buffer[], int size, int &max, int &min);
void MINMAX_recursion(int buffer[], int size, int &max, int &min);

int cost; // track cost complexity

// driver program
main( int argc, char *argv[] )
{
	ofstream out_MML, out_MMR;
	out_MML.open("min_max_search_loop_cost.txt", std::ios_base::app);
	//out_MAXL.open("max_search_loop_cost.txt", std::ios_base::app);
	out_MMR.open("min_max_search_recurse_cost.txt", std::ios_base::app);
	//out_MAXR.open("max_search_recurse_cost.txt", std::ios_base::app);

	int size;
	size = atoi(argv[1]);
	cout << "Size = " << size << endl;

	int buffer[size];

	cost = 0;

	/*
	init_array( buffer, size );
	shuffle_array( buffer, size );
	//show_array( buffer, size );
	int index = -1;

	min_search( buffer, size, index );
	//cout << "Min = " << buffer[index] << endl;
	cout << "Min Loop cost: " << cost << endl;
	out_MINL << cost << endl;
	cost = 0;
	
	init_array( buffer, size );
	shuffle_array( buffer, size );
	//show_array( buffer, size );
	index = -1;*/

	/*
	max_search( buffer, size, index );
	//cout << "Max = " << buffer[index] << endl;;
	cout << "Max Loop cost: " << cost << endl;
	out_MAXL << cost << endl;
	cost = 0;

	init_array( buffer, size );
	shuffle_array( buffer, size );
	index = -1;
	//show_array( buffer, size );

	min_search_recursion( buffer, size, index );
	//cout << "Min = " << index << endl;
	cout << "Min Recursion cost: " << cost << endl;
	out_MINR << cost << endl;
	cost = 0;
	
	init_array( buffer, size );
	shuffle_array( buffer, size );
	index = -1;
	//show_array( buffer, size );

	max_search_recursion( buffer, size, index );
	//cout << "Max = " << index << endl;
	cout << "Max Recursion cost: " << cost << endl;
	out_MAXR << cost << endl;
	cost = 0; */
	
	init_array( buffer, size );
	shuffle_array( buffer, size );
	int index_min = -1;
	int index_max = -1; 

	MINMAX_loop(buffer, size, index_max, index_min);
	cout << "MINMAX loop cost: " << cost << endl;
	out_MML << cost << endl;
	cost = 0;

	init_array( buffer, size );
	shuffle_array( buffer, size );
	index_min = -1;
	index_max = -1; 

	

	MINMAX_recursion(buffer, size, index_max, index_min);
	cout << "MINMAX recursion cost: " << cost << endl;
	out_MMR << cost << endl;
	cost = 0;

	/*
	select_sort( buffer, size );
	if ( is_sorted( buffer, size ) == 0 ) 
		cout << "Sort did not work!" << endl;
	else
		cout << "Array is sorted" << endl;
	show_array( buffer, size );
	*/

	out_MML.close();
	out_MMR.close();
	//out_MINR.close();
	//out_MAXR.close();
}

void init_array( int buffer[], int size )
{
	for ( int i=0; i<size; i++ ) {
		buffer[i] = i;
	}
}

void show_array( int buffer[], int size )
{
	cout << "[";
	for ( int i=0; i<size; i++ ) {
		cout << buffer[i] << " ";
	}
	cout << "]" << endl;
}

void shuffle_array( int buffer[], int size )
{
	srand(time(0));	// seed the random generator
	for ( int i=size; i>0; i-- ) {
		int index = rand() % i;	// index is in the range of [0,i-1]
		if ( index < i-1 ) 
			swap( buffer[index], buffer[i-1] );
	}
}

void min_search( int buffer[], int size, int &answer )
{
	int index = 0;
	for ( int i=1; i<size; i++ ) {
		cost++;
		if ( buffer[i] < buffer[index] ) // charge a unit cost here 
			index = i;
	}
	answer = index;
}

void max_search( int buffer[], int size, int &answer )
{
	int index = 0;
	for ( int i=1; i<size; i++ ) {
		cost++;
		if ( buffer[i] > buffer[index] ) // charge a unit cost here 
			index = i;
	}
	answer = index;
}

void min_search_recursion( int buffer[], int size, int &answer){
	if(size == 1) answer = buffer[0];
	else{
		int left_buffer_size = size/2;
		int right_buffer_size;
		if(size%2 == 1)
			right_buffer_size = (size/2)+1;
		else
			right_buffer_size = size/2;
		
		int left_buffer[left_buffer_size];
		int right_buffer[right_buffer_size];
		
		for(int i = 0; i < size/2; i++)
			left_buffer[i] = buffer[i];
		
		for(int i = 0; i < size/2 + 1; i++)
			right_buffer[i] = buffer[(size/2) + i];
	
		int left, right;
		
		min_search_recursion( left_buffer, left_buffer_size, left);
		min_search_recursion( right_buffer, right_buffer_size, right);
		
		if(left < right) answer = left;
		else answer = right;
		cost++;
	}
}

void max_search_recursion( int buffer[], int size, int &answer){
	if(size == 1) answer = buffer[0];
	else{
		int left_buffer_size = size/2;
		int right_buffer_size;
		if(size%2 == 1)
			right_buffer_size = (size/2)+1;
		else
			right_buffer_size = size/2;
		
		int left_buffer[left_buffer_size];
		int right_buffer[right_buffer_size];
	
		for(int i = 0; i < size/2; i++)
			left_buffer[i] = buffer[i];
		
		for(int i = 0; i < size/2 + 1; i++)
			right_buffer[i] = buffer[(size/2) + i];
	
		int left, right;
		
		max_search_recursion( left_buffer, left_buffer_size, left);
		max_search_recursion( right_buffer, right_buffer_size, right);
		
		if(left > right) answer = left;
		else answer = right;
		cost++;
	}
}

void MINMAX_loop(int buffer[], int size, int &max, int &min){
	int start_loop = 0;

	if(size%2 == 0){
		if(buffer[0] < buffer[1]){
			min = buffer[0];
			max = buffer[1];
			cost++;
		}
		else{
			min = buffer[1];
			max = buffer[0];
			cost++;
		}
		start_loop = 2;
	}
	else{
		min = buffer[0];
		max = buffer[1];
		start_loop = 1;
	}

	for ( int i=start_loop; i<size; i+=2 ) {
		cost+=3;
		if(buffer[i] < buffer[i+1]){
			if(buffer[i] < min) min = buffer[i];
			else if(buffer[i] > max) max = buffer[i];	
		}
	}
}

void MINMAX_recursion(int buffer[], int size, int &max, int &min){
	if(size == 1){
		min = buffer[0];
		max = buffer[0];
	}
	else if(size == 2){
		if(buffer[0] < buffer[1]){
			min = buffer[0]; 
			max = buffer[1];
		}
		else{
			min = buffer[1];
			max = buffer[0];
		}
		cost++;
	}
	else{
		int left_buffer_size = size/2;
		int right_buffer_size;
		if(size%2 == 1)
			right_buffer_size = (size/2)+1;
		else
			right_buffer_size = size/2;
		
		int left_buffer[left_buffer_size];
		int right_buffer[right_buffer_size];
	
		for(int i = 0; i < size/2; i++)
			left_buffer[i] = buffer[i];
		
		for(int i = 0; i < size/2 + 1; i++)
			right_buffer[i] = buffer[(size/2) + i];
	
		int left_min, left_max, right_min, right_max;
		
		MINMAX_recursion( left_buffer, left_buffer_size, left_max, left_min);
		MINMAX_recursion( right_buffer, right_buffer_size, right_max, right_min);
		
		if(left_min < right_min) min = left_min;
		else min = right_min;
		cost++;
		if(left_max > right_max) max = left_max;
		else max = right_max;
		cost++;
	}
}

void select_sort( int buffer[], int size )
{
	if ( size <= 1 ) return;
	int index;
	min_search( buffer, size, index );
	if ( index < size-1 )
		swap( buffer[index], buffer[size-1] );
	select_sort( buffer, size-1 );
}

int is_sorted( int buffer[], int size )
{
	for ( int i=0; i<size-1; i++ )
		if ( buffer[i] < buffer[i+1] )
			return 0;
	return 1;
}





