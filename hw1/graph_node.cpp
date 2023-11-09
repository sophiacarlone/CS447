//Sophia Carlone

#include<iostream>
#include<vector>

using namespace std;

class graph_node{
	private:
		switch_num_;
		vector<graph_node*> implies_; //pointers to implicaitons
	public:
		void track();	
};


void graph_node::track(){
	for(int i  = 0; i < implies_.size(); i++){
		
	} 
}
