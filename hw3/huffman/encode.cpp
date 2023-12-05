//hw3 babyyyyyyyyyyyyyyy!

//huffman encoding

#include<iostream>
#include<fstream>
#include<map>
#include<vector>
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
void msort(vector<tree_node> &array, int size);
void msort(vector<tree_node> &array, int low, int high);
void merge(vector<tree_node> &array, int low, int mid, int high);


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
	vector <struct tree_node> sorted_symbols;
	struct tree_node insertnode;
	string jank = "";
	int curr_head = 0;
	for(auto it = symbol_map.begin(); it != symbol_map.end(); it++){
		jank += it->first;
		insertnode = {jank, it->second.frequency, NULL, NULL};
		sorted_symbols.push_back(insertnode);
		curr_head++;
		jank = "";
	}
for(int i = 0; i < sorted_symbols.size(); i++){
		cout << sorted_symbols[i].symbols <<  " " << sorted_symbols[i].value << endl;
	}
	cout << endl;

	msort(sorted_symbols, num_characters); 
	for(int i = 0; i < sorted_symbols.size(); i++){
		cout << sorted_symbols[i].symbols <<  " " << sorted_symbols[i].value << endl;
	}
	cout << endl;
	struct tree_node created_node;

while(sorted_symbols.size() > 1){
		created_node.symbols = sorted_symbols[sorted_symbols.size()-2].symbols + sorted_symbols[sorted_symbols.size()-1] .symbols;
		created_node.value = sorted_symbols[sorted_symbols.size()-2].value + sorted_symbols[sorted_symbols.size()-1] .value;
		created_node.left_child = &sorted_symbols[sorted_symbols.size()-2]; //TODO: repalce with pop_back()?
		created_node.right_child = &sorted_symbols[sorted_symbols.size()-1];

		cout << "newly created node " << created_node.symbols << " " << created_node.value << endl;

		sorted_symbols.pop_back();
		sorted_symbols.pop_back();

		sorted_symbols.push_back(created_node);

	cout << "new vector" << endl;
		for(int i = 0; i < sorted_symbols.size(); i++){
			cout << sorted_symbols[i].symbols <<  " " << sorted_symbols[i].value << endl;
		}

		msort(sorted_symbols, sorted_symbols.size()); 
		cout << endl;

		cout << "new vector sorted" << endl;
		for(int i = 0; i < sorted_symbols.size(); i++){
			cout << sorted_symbols[i].symbols <<  " " << sorted_symbols[i].value << endl;
		}
		cout << endl;
}

	return 0;
}

//merge sort
void msort(vector<tree_node> &array, int size){
	msort(array, 0, size-1);
}

//merge sort helper
void msort(vector<tree_node> &array, int low, int high){
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
void merge(vector<tree_node> &array, int low, int mid, int high){
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
