#include<iostream>
#include<vector>

using namespace std;

class node{ //class specifically for tracking and representation of the lightbulb graph
	private:
		int switch_ID_; //id of the switch either in on (+) or off (-) form (cannot be 0)
		bool seen_; //has it been accounted for in BFS QUESTION: will this be necessary?
		int value_; //hold the ideal value based on tracking results (0/1)
		vector<*node> edges_; //pointers to what this node should imply. This of this as edges
	public:
		void node(int id);
		void Add_edges(const vector<*node>& implies);
		void print_edges(); 
};

void node::node(int id){
	switch_ID_ = id;
	seen_ = false;
	value = -1;
	edges_ = NULL;
}

void node::Add_edges(const vector<*node>& implies){
	edges_ = implies;
}

void print_edges(){
	for(int i = 0; i < edges_.size(); i++){
		cout << edges[i].switch_ID_ << " ";
	}
	cout << endl;
} 

int main(){
	node n1 = new node(1);
	node n2 = new node(2);
	node n3 = new node(3);
	node n4 = new node(4);

	vector<*nodes> fringe;
	fringe.push_back(n2);	
	fringe.push_back(n3);	
	fringe.push_back(n4);	
		
	n1.Add_edges(fringe);

	return 0;
}

/*
class graph_node{
	private:
		int switch_num_;
		vector<graph_node*> implies_; //pointers to implicaitons
		bool seen_;
	public:
		void BFS(const graph_node* origin, int size);	
};


void graph_node::BFS(const graph_node* origin, int size){
	graph_node fringe[size];
	int start = 0;
	int next_space = 1;
	fringe[start] = *origin;
	do{
		for(int i  = 0; i < implies_.size(); i++){
			fringe[next_space] = implies_[i];
			next_space++;
		}
		fringe[start].seen_ = true;
		start++;
	}while(fringe[start] == false);

	for(int i = 0; i < size; i++){
		cout << fringe[i] << " ";
	}
	cout << endl;
} */
