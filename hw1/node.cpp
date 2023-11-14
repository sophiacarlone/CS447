#include<iostream>
#include<vector>

using namespace std;

class node{ //class specifically for tracking and representation of the lightbulb graph
	private:
		int switch_ID_; //id of the switch either in on (+) or off (-) form (cannot be 0)
		bool seen_; //has it been accounted for in BFS QUESTION: will this be necessary?
		int value_; //hold the ideal value based on tracking results (0/1)
		//vector<node *> edges_; //pointers to what this node should imply. This of this as edges QUESTION: should this be in public?
	public:
		vector<node *> edges_; //pointers to what this node should imply. This of this as edges QUESTION: should this be in public?
		node(int id); //constructor
		void Add_edges(const vector<node *>& implies); //add edges of the vector
		//TOD0: add edge one at a time
		void print_edges(); 
		int getSwitchID(){return switch_ID_;};
		int getNumEdges(){return edges_.size();}; //TOD0: get rid of this
		void setSeen(bool x){ seen_ = x; };
		bool getSeen(){ return seen_; };
};

node::node(int id){
	switch_ID_ = id;
	seen_ = false;
	value_ = -1;
	edges_ = vector<node *>();
}

void node::Add_edges(const vector<node *>& implies){
	edges_ = implies;
}

void node::print_edges(){
	for(int i = 0; i < edges_.size(); i++){
		cout << edges_[i]->switch_ID_ << " ";
	}
	cout << endl;
} 

//prototypes
//void BFS(node * origin, int size);
bool Track(node * origin, int size);

int main(){
	node n1 (1);
	node n2 (2);
	node n3 (3);
	node n4 (4);
	node n5 (5);
	node n6 (6);
	node n7 (7);
	node nneg1 (-1);

	vector<node *> fringe;
	fringe.push_back(&n2);	
	fringe.push_back(&n3);	
	fringe.push_back(&n4);	
		
	n1.Add_edges(fringe);

	vector<node *> f2;
	f2.push_back(&n5);	
	f2.push_back(&n6);	
	
	n2.Add_edges(f2);

	//n1.print_edges();
	//n2.print_edges();

	vector<node *>f3;
	f3.push_back(&n1);
	f3.push_back(&n7);
	f3.push_back(&nneg1);
	n4.Add_edges(f3);
	
	//n4.print_edges();

	//BFS(&n1, 7);
	//cout << "tracking now" << endl;
	bool found = Track(&n1, 8);
	//cout << "tracking done" << endl;

	cout << "was it found? " << found << endl;	

	return 0;
}

/*
void BFS(node * origin, int size){
	node * fringe[size];
	int curr_head = 0;
	int next_space = 1;
	fringe[curr_head] = origin;
	
	do{
		//if(fringe[curr_head]->getSeen()){
		//	continue;
		//} 
		//cout << "hit B" << endl;
		for(int i = 0; i < fringe[curr_head]->getNumEdges(); i++){
			if(!(fringe[curr_head]->edges_[i]->getSeen())){
			fringe[next_space] = fringe[curr_head]->edges_[i];
			//cout << fringe[next_space]->getSwitchID() << " ";
			next_space++;
			}
			//cout << endl << "next space # is " << next_space << endl;
			for(int j = 0; j < size; j++){
				cout << fringe[j]->getSwitchID() << " ";
			}
			cout << endl;	
		}
		fringe[curr_head]->setSeen(true);
		curr_head++;
	}while(curr_head < size);

	for(int i = 0; i < size; i++){
		cout << fringe[i]->getSwitchID() << " ";
	}
	cout << endl;		
}*/

bool Track(node * origin, int size){ //track and chase
	cout << "Tracking now" << endl;
	//BFS
	node * fringe[size];
	int curr_head = 0;
	int next_space = 1;
	fringe[curr_head] = origin;
	
	do{
		//if(fringe[curr_head]->getSeen()){
		//	continue;
		//} 
		//cout << "hit B" << endl;
		for(int i = 0; i < fringe[curr_head]->getNumEdges(); i++){
			if(!(fringe[curr_head]->edges_[i]->getSeen())){
			fringe[next_space] = fringe[curr_head]->edges_[i];
			//cout << fringe[next_space]->getSwitchID() << " ";
			next_space++;
			}
			//cout << endl << "next space # is " << next_space << endl;
			//for(int j = 0; j < size; j++){
			//	cout << fringe[j]->getSwitchID() << " ";
			//}
			//cout << endl;	
		}
		fringe[curr_head]->setSeen(true);
		curr_head++;
	}while(curr_head < size);
/*
	for(int i = 0; i < size; i++){
		cout << fringe[i]->getSwitchID() << " ";
	}
	cout << endl;
*/
	//END OF BFS
	
	for(int i = 0; i < size; i++){
		if(fringe[i]->getSwitchID() == (-1 * origin->getSwitchID())) return true;
	}
	return false;	
}





/*************GARBAGE SHOOT*************/

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
