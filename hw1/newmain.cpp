#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<stdlib.h>

using namespace std;

//DATA STRUCTURES
class node{ //class specifically for tracking and representation of the lightbulb graph
	private:
		int switch_ID_; //id of the switch either in on (+) or off (-) form (cannot be 0)
		bool seen_; //has it been accounted for in BFS QUESTION: will this be necessary?
		int value_; //hold the ideal value based on tracking results (0/1)
		bool confirmed_; //Is the value held by this node confirmed?
		//vector<node *> edges_; //pointers to what this node should imply. This of this as edges QUESTION: should this be in public?
	public:
		vector<node *> edges_; //pointers to what this node should imply. This of this as edges QUESTION: should this be in public?
		node();
		//node(int id); //constructor
		void Add_edges(const vector<node *>& implies); //add edges of the vector
		//TOD0: add edge one at a time
		void print_edges(); 
		int getSwitchID(){return switch_ID_;};
		void setSwitchID(int x){switch_ID_ = x;};
		int getNumEdges(){return edges_.size();}; //TOD0: get rid of this
		void setSeen(bool x){ seen_ = x; };
		bool getSeen(){ return seen_; };
		void setValue(int x){ value_ = x; };
		int getValue(){ return value_; };
		int setConfirmed(bool x){ confirmed_ = x; };
		//TOD0: Destructor
};

node::node(){ //TOD0: big clean
	switch_ID_ = 0;
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

//Globals
map<int, node> graph; //graph that will hold all implications

//PROTOTYPES
//void BFS(node * origin, int size);
bool Track(node * origin, int size);
void Result(node * origin, bool x2negx, bool negx2x);

void lightbulbs(){
    int bulbs; //total bulbs
    int switches; //total switches
    int curr_switch1; //switch being looked at at one time
    int curr_switch2; //switch being looked at at one time
    //map<int, node> graph; //graph that will hold all implications

    ifstream in;
    in.open("instance.txt");
    in >> switches >> bulbs;
	//cout << switches << " " << bulbs << endl;
    node switchNum; //it goes back up here to call the implicit deallocator

    for(int i = 1; i <= switches; i++){ 
	switchNum.setSwitchID(i);
	graph[i] = switchNum;
	switchNum.setSwitchID(-1*i);
	graph[-1*i] = switchNum;

    }

//for testing
/*    for(int i = 1; i <= switches; i++){ //QUESTION: why -1?
	//switchNum.setValue(i);
	cout << graph[i].getSwitchID() << " ";
    }
	cout << endl;
*/
    for (int i = 0; i < bulbs; i++){

	//a | b
        in >> curr_switch1; //get switch being looked at
        in >> curr_switch2; //get switch being looked at
/*
	if(graph.find(curr_switch1) == graph.end()){ //see if its in
		node nx = new node;
		nx(curr_switch1); //TOD0: get rid of the set id since it will be the key of the map called graph
		graph.insert(pair<int, node>(curr_switch, nx));
	}
	if(graph.find(curr_switch2) == graph.end()){ //see if its in
		node nx = new node(curr_switch2); 
		graph.insert(pair<int, node>(curr_switch2, nx));
	}
	if(graph.find(-1 * curr_switch1) == graph.end()){ //see if its in
		node nx = new node(-1 * curr_switch1); 
		graph.insert(pair<int, node>(-1 * curr_switch1, nx));
	}
	if(graph.find(-1 * curr_switch2) == graph.end()){ //see if its in
		node nx = new node(-1 * curr_switch2); 
		graph.insert(pair<int, node>(-1 * curr_switch2, nx));
	}
*/
	//cout << curr_switch1 <<endl; // ~a->b
	//cout << curr_switch2 << endl; // ~a->b
	graph[-1*curr_switch1].edges_.push_back(&graph[curr_switch2]); // ~a->b
	graph[-1*curr_switch2].edges_.push_back(&graph[curr_switch1]); // ~b->a

    }

    for(int i = 1; i <= switches; i++){ //QUESTION: why -1?
	//switchNum.setValue(i);
	cout << i << ": ";
	graph[i].print_edges();
	cout << -1*i << ": ";
	graph[-1*i].print_edges();
    }
	cout << endl;

    //return graph;
}

//FUNCTIONS
int main(){
	//map<int, node> graph;
	lightbulbs(); //TOD0: argc for filename
	int switches = graph.size()/2;
	int tracked_posneg, tracked_negpos;

/*    for(int i = 1; i <= switches; i++){ //QUESTION: why -1?
	//switchNum.setValue(i);
	graph[i].print_edges();
	graph[-1*i].print_edges();
    }
	cout << endl;
*/
    for(int i = 1; i <= switches; i++){ 
//	cout << endl;
	tracked_posneg = Track(&(graph[i]), graph.size());
//	cout << endl;
	tracked_negpos = Track(&(graph[-1*i]), graph.size());
	Result(&(graph[i]), tracked_posneg, tracked_negpos);
    }

	return 0;
}

bool Track(node * origin, int size){ //track and chase
//	cout << "switch id " << origin->getSwitchID() << " " << endl;
//	cout << "edges: ";
//	origin->print_edges();
	if(origin->edges_.size() == 0) return false;
	//BFS
	vector<node *> fringe;
	//node * fringe[size];
	int curr_head = 0;
	//int next_space = 1;
	fringe.push_back(origin);
	//fringe[curr_head] = origin;
	
	do{
//		cout << "in do" << endl;
//		cout << "curr head: " << curr_head << " fringe size: " << fringe.size() << endl;
		//if something has no edges, we should break
//		fringe[curr_head]->print_edges();
//		cout << "HIIIIIII" << endl;
		if(fringe[curr_head]->getNumEdges() == 0){ 
			if(curr_head == fringe.size()-1) break;
			continue;
		}
		for(int i = 0; i < fringe[curr_head]->getNumEdges(); i++){
			if(!(fringe[curr_head]->edges_[i]->getSeen())){
				fringe.push_back(fringe[curr_head]->edges_[i]);
				//fringe[next_space] = fringe[curr_head]->edges_[i];
				//next_space++;
			}
		}
		fringe[curr_head]->setSeen(true);
//		cout << "hit 1" << endl;
		curr_head++;
//		for(int i = 0; i < fringe.size(); i++){
//			cout << fringe[i]->getSwitchID() << " ";
//		}
//		cout << endl;
//		fringe[curr_head]->print_edges();

	}while(curr_head < size); //TOD0: fix
/*
	for(int i = 0; i < size; i++){
		cout << fringe[i]->getSwitchID() << " ";
	}
	cout << endl;
*/
	//END OF BFS
	
	for(int i = 0; i < fringe.size(); i++){
		fringe[i]->setSeen(false);//reset
		if(fringe[i]->getSwitchID() == (-1 * origin->getSwitchID())) return true;
	}
	return false;	
}

void Result(node * origin, bool x2negx, bool negx2x){
	if(x2negx && negx2x){
		cout << "NO SOLUTION" << endl;
		exit(0);
	}
	if(x2negx && !negx2x){
		origin->setValue(0);
		origin->setConfirmed(true);
		cout << "set origin value to " << origin->getValue() << endl;
		//could possibly set up the start of the chase here
	}
	else if(!x2negx && negx2x){ //leaving this as else if because later there may be a chase
		origin->setValue(1);
		origin->setConfirmed(true);
		cout << "set origin value to " << origin->getValue() << endl;
		//all lightbulbs where x1 being on implies the lightbulb is off, we got a problem
	}
	//possible else to start a chase
}
