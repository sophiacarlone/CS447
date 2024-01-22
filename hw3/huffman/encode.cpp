//huffman encoding

#include<iostream>
#include<fstream>
#include<map>
#include<queue>
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
void add_to_front(string &original, char new_char);
void BFS(tree_node& tree, vector<string> &array);

int main(int argc, char *argv[]){
	string filename = argv[1];
	fstream in;
	//int total_symbols = 0;
	map<char, symbol> symbol_map;
	// map<int, symbol> sorted_nodes; //jank?

	//input and frequencies
	struct symbol curr_symbol;
	char curr_char;
	in.open(filename.c_str()); //TODO: assert
	while(in >> noskipws >> curr_char){
		//in >> curr_char;
		//total_symbols++;
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

	//turn the map into a vector that will be sorted
	for(auto it = symbol_map.begin(); it != symbol_map.end(); it++){
		jank += it->first;
		insertnode = {jank, it->second.frequency, NULL, NULL};
		sorted_symbols.push_back(insertnode);
		curr_head++;
		jank = "";
	}

/*
for(int i = 0; i < sorted_symbols.size(); i++){
		cout << sorted_symbols[i].symbols <<  " " << sorted_symbols[i].value << endl;
	}
	cout << endl; 
*/
	struct tree_node created_node;
//	int num_of_new_nodes_created = 0;

while(sorted_symbols.size() > 1){ //when the vector is equal to 1, that means we have made the main tree
//	cout << "in while" << endl;
		msort(sorted_symbols, sorted_symbols.size()); //sort the nodes 
/*
		cout << "new vector sorted" << endl;
		for(int i = 0; i < sorted_symbols.size(); i++){
			cout << sorted_symbols[i].symbols <<  " " << sorted_symbols[i].value << endl;
		}
*/
		//create a new node with the two nodes at the end of the sorted vector
		created_node.symbols = sorted_symbols[sorted_symbols.size()-2].symbols + sorted_symbols[sorted_symbols.size()-1] .symbols;
		created_node.value = sorted_symbols[sorted_symbols.size()-2].value + sorted_symbols[sorted_symbols.size()-1] .value;
		created_node.left_child = &sorted_symbols[sorted_symbols.size()-2]; //TODO: replace with pop_back()?
		created_node.right_child = &sorted_symbols[sorted_symbols.size()-1];

		cout << "created node left child " << created_node.left_child->symbols << endl;
		cout << "created node rightt child " << created_node.right_child->symbols << endl;
//		num_of_new_nodes_created++;
		cout << "newly created node " << created_node.symbols << " " << created_node.value << endl;

		//remove the last two nodes and replace with their new parent node
		sorted_symbols.pop_back();
		sorted_symbols.pop_back();

		sorted_symbols.push_back(created_node);
		cout << "created node left child " << created_node.left_child->symbols << endl;
		cout << "created node rightt child " << created_node.right_child->symbols << endl;
/*
	cout << "new vector" << endl;
		for(int i = 0; i < sorted_symbols.size(); i++){
			cout << sorted_symbols[i].symbols <<  " " << sorted_symbols[i].value << endl;
		}

		cout << endl;
*/
		cout << endl;

}

	cout << "hi" << endl;
	cout << "claimed left child: " << sorted_symbols[0].left_child->symbols << endl;
	cout << "hi" << endl;
	cout << sorted_symbols[0].right_child->symbols << endl;
	cout << "hi" << endl;
	//cout << sorted_symbols[0].symbols << endl;
	//cout << sorted_symbols[0].value << endl;

	//turning vector into an array which will be easier for printing and finding the encoding of each character
	//string symbol_array[num_of_new_nodes_created + num_characters];
	vector <string> symbol_vector;
	//BFS
	BFS(sorted_symbols[0], symbol_vector);

	cout << "new vector" << endl;
	for(int i = 0; i < symbol_vector.size(); i++){
		cout << symbol_vector[i] << endl;
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

void add_to_front(string &original, char new_char){
	original  = new_char + original;
}

void BFS(tree_node &tree, vector<string> &array){
	cout << "hit a" << endl;
	cout << "has node left child " << tree.left_child->symbols << endl;
	cout << "has node rightt child " << tree.right_child->symbols << endl;

	queue<tree_node> unvisitedFringe;
	//int number_of_inserts = 0;
	//int curr_head = 0;

	unvisitedFringe.push(tree);
	array.push_back(tree.symbols);
	//number_of_inserts++;
	//curr_head_array++; //I can combine this with line above, but I believe this is easier to read
	
	while(true){
		if(unvisitedFringe.size() == 0) {
			cout << "something went wrong in BFS" << endl;
			exit(2);
		}
		struct tree_node curr_head = unvisitedFringe.front();
		if(curr_head.left_child == NULL && curr_head.right_child == NULL){
			if(curr_head.symbols == unvisitedFringe.back().symbols) return; //cheating! doing .symbols instead of making a =
			array.push_back("-");
			//number_of_inserts++;
			array.push_back("-");
			//number_of_inserts++;		
		}
		unvisitedFringe.push(*(curr_head.left_child));
		array.push_back(curr_head.left_child->symbols);
		cout << (curr_head.left_child->symbols) << endl;
		unvisitedFringe.push(*(curr_head.right_child));
		array.push_back(curr_head.right_child->symbols);
		cout << (curr_head.right_child->symbols) << endl;
		unvisitedFringe.pop();
	}
}

/*
void DFS(tree_node& tree, char character){
	stack<tree_node> unvisitedFringe;
	string encoding = "";

	unvisitedFringe.push(tree);
	while(true){
		if(unvisitedFringe.size() == 0){
			cout << "character not found" << endl;
			exit(2); 
		}
		tree_node currentNode = unvisitedFringe.top();
        unvisitedFringe.pop();
		if (currentNode.symbols == character) return encoding; 
		else{
			for(int i = 0; i < actions.size(); i++)
				unvisitedFringe.push(successor(currentNode.state_, actions[i]));
		}
	}
}*/
