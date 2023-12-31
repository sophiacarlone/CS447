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
	public:
		vector<node *> edges_; //pointers to what this node should imply. This of this as edges QUESTION: should this be in public?
		node();
		//node(int id); //constructor
		bool getConfirmed(){return confirmed_;};
		void Add_edges(const vector<node *>& implies); //add edges of the vector
		void print_edges(); 
		int getSwitchID(){return switch_ID_;};
		void setSwitchID(int x){switch_ID_ = x;};
		int getNumEdges(){return edges_.size();}; //TOD0: get rid of this
		void setSeen(bool x){ seen_ = x; };
		bool getSeen(){ return seen_; };
		void setValue(int x){ value_ = x; };
		int getValue(){ return value_; };
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
vector <pair <int,int> > lightbulbs(string filename); //input
bool Track(node * origin, int size); //bfs for graph
void Result(node * origin, bool x2negx, bool negx2x); //checks to see if solution is possible


//FUNCTIONS
int main(int argc, char *argv[]){
	string filename = argv[1];
	vector<pair <int,int> > configuration = lightbulbs(filename); 
	int bulbs = configuration.front().second;
	int switches = configuration.front().first;
	int tracked_posneg, tracked_negpos;

	//what can we assume and is there a solution
    for(int i = 1; i <= switches; i++){ 
	tracked_posneg = Track(&(graph[i]), graph.size());
	tracked_negpos = Track(&(graph[-1*i]), graph.size());
	Result(&(graph[i]), tracked_posneg, tracked_negpos);
    }
	
    for (int i = 1; i<= switches; i++){
	if (graph[i].getValue() == -1){
			graph[i].setValue(rand()%2);
	}
    }

	//random walk
    bool cheesy = false;
    while (!cheesy){
        cheesy = true;
        for (int i = 1; i<= switches; i++){
            if(!graph[i].getConfirmed()){ // if editable
                for (int j = 1; j < bulbs + 1; j++){  //check all bulbs

                    int b1 = configuration[j].first;
                    int b2 = configuration[j].second;

                    if ((b1 == ((-1*(graph[i].getValue()))*i)) && (b2 == ((-1*(graph[b2].getValue()))*i))){ 
                	// if the first switch is the oppoiste of i, and the second switch is also wrong, swap first
                        graph[i].setValue(-1*graph[i].getValue()*graph[i].getSwitchID());
                        cheesy = false;
                        
                    }
                    else if ((b2 == ((-1*(graph[i].getValue()))*i)) && (b1 == ((-1*(graph[b1].getValue()))*i))){ 
                	// if the first switch is wrong, and the second switch the opposite of i, swap second
                        graph[i].setValue(-1*graph[i].getValue()*graph[i].getSwitchID());
                        cheesy = false;
                    }
                }
            }
        }
    }

	//print out solution
	cout << "Proof: " << endl;
	for(int i = 1; i <= switches; i++){
		if(graph[i].getValue()) cout << graph[i].getSwitchID() << " ";
		else cout << graph[i].getSwitchID() * -1 << " ";
	}
	cout << endl;
	return 0;
}

vector <pair <int,int> > lightbulbs(string filename){
    int bulbs; //total bulbs
    int switches; //total switches
    int curr_switch1; //switch being looked at at one time
    int curr_switch2; //switch being looked at at one time
    vector<pair <int,int> > bulb_confs; // bulb configuration for checking later

    ifstream in;
    in.open(filename);
    in >> switches >> bulbs;
    pair <int,int> cheese (switches,bulbs);
    bulb_confs.push_back(cheese);
    node switchNum; //it goes back up here to call the implicit deallocator

    for(int i = 1; i <= switches; i++){ 
	switchNum.setSwitchID(i);
	graph[i] = switchNum;
	switchNum.setSwitchID(-1*i);
	graph[-1*i] = switchNum;

    }

    for (int i = 0; i < bulbs; i++){

	//a | b
        in >> curr_switch1; //get switch being looked at
        in >> curr_switch2; //get switch being looked at
        cheese.first = curr_switch1;
        cheese.second = curr_switch2;
        bulb_confs.push_back(cheese);
	graph[-1*curr_switch1].edges_.push_back(&graph[curr_switch2]); // ~a->b
	graph[-1*curr_switch2].edges_.push_back(&graph[curr_switch1]); // ~b->a

    }

/*    for(int i = 1; i <= switches; i++){ 
	//switchNum.setValue(i);
	cout << i << ": ";
	graph[i].print_edges();
	cout << -1*i << ": ";
	graph[-1*i].print_edges();
    }
	cout << endl;
*/ 
    return bulb_confs;
}

bool Track(node * origin, int size){ //track and chase
	if(origin->edges_.size() == 0) return false;
	//BFS
	vector<node *> fringe;
	int curr_head = 0;
	bool ability_to_continue;
	fringe.push_back(origin);
	do{
		//if something has no edges, we should break
		if(fringe[curr_head]->edges_.size() == 0){ 
			if(curr_head == fringe.size()-1) break;
			continue;
		//if a node has edges that have all been seen, we should break
		ability_to_continue = false;
		}
		for(int i = 0; i < fringe[curr_head]->getNumEdges(); i++){
			if(!(fringe[curr_head]->edges_[i]->getSeen())){
				fringe.push_back(fringe[curr_head]->edges_[i]);
				fringe[curr_head]->edges_[i]->setSeen(true);
				ability_to_continue = true;
			}
		}
		if(!ability_to_continue) break;
		fringe[curr_head]->setSeen(true);

		//getting edge cases
		ability_to_continue = false;
		if(curr_head == fringe.size()-1){
			for(int i = 0; i < fringe[curr_head]->getNumEdges(); i++) if(!(fringe[curr_head]->edges_[i]->getSeen())) ability_to_continue = true;
		}
		if(!ability_to_continue) break;
		
		curr_head++;
		
		if(curr_head >=fringe.size()) break;
		if(fringe[curr_head]->getSwitchID() == origin->getSwitchID()) break;
 
	}while(curr_head < size); 

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
		cout << "set origin value to " << origin->getValue() << endl;
	}
	else if(!x2negx && negx2x){ //leaving this as else if because later there may be a chase
		origin->setValue(1);
		cout << "set origin value to " << origin->getValue() << endl;
		//all lightbulbs where x1 being on implies the lightbulb is off, we got a problem
	}
}
