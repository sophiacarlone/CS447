//hw3 babyyyyyyyyyyyyyyy!

//huffman encoding

#include<iostream>
#include<fstream>
#include<map>
//#include"tree.cpp"

using namespace std;

//custom structures
struct symbol{
	int frequency;
	string encoding;
	char letter;
};

struct node{  
    string symbols;
    int value;
};

struct tree_node{
	string symbols;
    int value;
	struct tree_node * left_child;
	struct tree_node * right_child;
};

//functions
void msort(tree_node array[], int size);
void msort(tree_node array[], int low, int high);
void merge(tree_node array[], int low, int mid, int high);


int main(int argc, char *argv[]){
	string filename = argv[1];
	fstream in;
	int total_symbols = 0;
	map<char, symbol> symbol_map;
	// map<int, symbol> sorted_nodes; //jank?

	//input and frequencies
	struct symbol curr_symbol;
	char curr_char;
	in.open(filename.c_str()); //TODO: assert
	while(in >> noskipws >> curr_char){
		//in >> curr_char;
		total_symbols++;
		auto it = symbol_map.find(curr_char);
		if(it == symbol_map.end()){
			curr_symbol = {1, "", curr_char};
			symbol_map[curr_char] = curr_symbol;
		}
		else{
			symbol_map[curr_char].frequency++;
		}
	}

	int num_characters = symbol_map.size();

	// for(auto it = symbol_map.begin(); it != symbol_map.end(); it++){
	// 		//it->second.frequency /= total_symbols;
	// 		cout << it->first << " has a frequency of " << it->second.frequency << endl;
	// }

	//sorting of frequencies
	struct tree_node sorted_symbols[num_characters];
	struct tree_node insertnode;
	string jank = "";
	int curr_head = 0;
	for(auto it = symbol_map.begin(); it != symbol_map.end(); it++){
		jank += it->first;
		insertnode = {jank, it->second.frequency, NULL, NULL};
		sorted_symbols[curr_head] = insertnode;
		curr_head++;
		jank = "";
	}

	msort(sorted_symbols, num_characters); //TODO: at this point, size should be its own variable

	struct tree_node created_node;
	created_node.symbols = sorted_symbols[num_characters-2].symbols + sorted_symbols[num_characters-1] .symbols;
	created_node.value = sorted_symbols[num_characters-2].value + sorted_symbols[num_characters-1] .value;
	created_node.left_child = &sorted_symbols[num_characters-2];
	created_node.right_child = &sorted_symbols[num_characters-1];

	
	// symbol_map[sorted_symbols[num_characters-2].symbols].encoding = "0" + symbol_map[sorted_symbols[num_characters-2].symbols].encoding;
	// symbol_map[sorted_symbols[num_characters-1].symbols].encoding = "1" + symbol_map[sorted_symbols[num_characters-1].symbols].encoding;

	
	// for(int i = 0; i < num_characters; i++){
	// 	cout << sorted_symbols[i].symbols << endl;
	// }


	return 0;
}

//merge sort
void msort(tree_node array[], int size){
	msort(array, 0, size-1);
}

//merge sort helper
void msort(tree_node array[], int low, int high){
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
void merge(tree_node array[], int low, int mid, int high){
	int size = high-low+1;
	tree_node temp[size];

	int left = low; //start
	int right = mid+1;

	int index = 0;
	while(left <= mid && right <= high){
		if(array[left].value > array[right].value){
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
