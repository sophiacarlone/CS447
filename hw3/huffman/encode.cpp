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

//functions
void msort(node array[], int size);
void msort(node array[], int low, int high);
void merge(node array[], int low, int mid, int high);


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
	while(in >> curr_char){
		//in >> curr_char;
		total_symbols++;
		auto it = symbol_map.find(curr_char);
		if(it == symbol_map.end()){
			//cout << "hit A on " << curr_char << endl;
			curr_symbol = {1, "", curr_char};
			symbol_map[curr_char] = curr_symbol;
			//cout << symbol_map[curr_char].frequency <<endl;
		}
		else{
			//cout << "hit B on " << curr_char << endl;
			symbol_map[curr_char].frequency++;
			//cout << symbol_map[curr_char].frequency <<endl;
		}
	}

	// for(auto it = symbol_map.begin(); it != symbol_map.end(); it++){
	// 		//it->second.frequency /= total_symbols;
	// 		cout << it->first << " has a frequency of " << it->second.frequency << endl;
	// }

	//sorting of frequencies
	struct node sorted_symbols[symbol_map.size()];
	struct node insertnode;
	string jank = "";
	int curr_head = 0;
	// cout << "hit" << endl;
	for(auto it = symbol_map.begin(); it != symbol_map.end(); it++){
		jank += it->first;
		//cout << jank << endl;
		insertnode = {jank, it->second.frequency};
		// cout << insertnode.symbols << endl;
		sorted_symbols[curr_head] = insertnode;
		curr_head++;
		jank = "";
	}

	for(int i = 0; i < symbol_map.size(); i++){
		cout << sorted_symbols[i].symbols << endl;
	}
	cout << "sorting" << endl;
	msort(sorted_symbols, symbol_map.size()); //TODO: at this point, size should be its own variable
	
	for(int i = 0; i < symbol_map.size(); i++){
		cout << sorted_symbols[i].symbols << endl;
	}
	return 0;
}

//merge sort
void msort(node array[], int size){
	msort(array, 0, size-1);
}

//merge sort helper
void msort(node array[], int low, int high){
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
void merge(node array[], int low, int mid, int high){
	int size = high-low+1;
	int temp[size];

	int left = low; //start
	int right = mid+1;

	int index = 0;
	while(left <= mid && right <= high){
		if(array[left].value < array[right].value){
			temp[index++] = array[left++].value;
		}
		else temp[index++] = array[right++].value;
	}
	while(left <= mid){
		temp[index++] = array[left++].value;
	}
	while(right <= high){
		temp[index++] = array[right++].value;
	}
	for(int i = 0; i < size; i ++){
		array[low+i].value = temp[i];
	}
}
