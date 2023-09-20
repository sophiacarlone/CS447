#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

int cost; // track cost complexity

// driver program
main( int argc, char *argv[] )
{
	int size;
	size = atoi(argv[1]);
	cout << "Size = " << size << endl;

	int buffer[size];

	cost = 0;

	init_array( buffer, size );
	shuffle_array( buffer, size );
	show_array( buffer, size );
	int index = -1;

	min_search( buffer, size, index );
	cout << "Min = " << buffer[index] << endl;
	cout << "cost: " << cost << endl;
	cost = 0;
	
	init_array( buffer, size );
	shuffle_array( buffer, size );
	show_array( buffer, size );
	index = -1;

	max_search( buffer, size, index );
	cout << "Max = " << buffer[index] << endl;;
	cout << "cost: " << cost << endl;
	cost = 0;

	init_array( buffer, size );
	shuffle_array( buffer, size );
	index = -1;
	show_array( buffer, size );

	min_search_recursion( buffer, size, index );
	cout << "Min = " << index << endl;
	cout << "cost: " << cost << endl;
	cost = 0;
	
	init_array( buffer, size );
	shuffle_array( buffer, size );
	index = -1;
	show_array( buffer, size );

	max_search_recursion( buffer, size, index );
	cout << "Max = " << index << endl;
	cout << "cost: " << cost << endl;
	cost = 0;
	
	select_sort( buffer, size );
	if ( is_sorted( buffer, size ) == 0 ) 
		cout << "Sort did not work!" << endl;
	else
		cout << "Array is sorted" << endl;
	show_array( buffer, size );
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





