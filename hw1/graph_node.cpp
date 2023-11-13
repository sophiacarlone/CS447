#include<iostream>
#include<vector>

using namespace std;

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
}
