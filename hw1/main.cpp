#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//Input
vector<pair<int,int>> lightbulbs(string filename){
    int bulbs;
    int switches;
    ifstream in;
    in.open(filename);
    in >> bulbs >> switches;
    pair<int,int> switch_conf;
    vector<pair<int,int>> bulb_confs;
    pair<int,int> params;
    params.first = bulbs;
    params.second = switches;
    bulb_confs.push_back(params);
    for (int i = 0; i < bulbs - 1; i++){
        in >> switch_conf.first;
        in >> switch_conf.second;
        bulb_confs.push_back(switch_conf);
    }
    for (pair<int,int> p : bulb_confs){
        cout << p.first << p.second;
    }
    return bulb_confs;
}

//my shit
void contradiction(){

}

int main(){
	vector<pair<int,int>> configuration = lightbulbs("3.txt"); //TOD0: should input what .txt we want using argc
	int bulbs, switches;
	bulbs = configuration.front().first;
	switches = configuration.front().second;

	pair <bool,bool> solution[switches];
	for (int i = 0; i< switches; i++){
  		solution[i].first = 0;
  		solution[i].second = (rand()%2);
	}

	//call contradictions

	int x = 0;
	while (x == 0){


  		for (int i = 0; i< switches; i++){
    			if(solution[i].first = 0){ // if editable

      				for (int j = 1; j < bulbs + 1; j++){  //check all bulbs

        				int b1 = configuration[j].first;
        				int b2 = configuration[j].second;

        				if ((b1-1 == ((1-2*(solution[i].second))*i)) && (solution[b2-1].first == 1)){ 
					// if the first switch is wrong, and the second switch isn't editable, swap and end loop
          					solution[i].second = !solution[i].second;
          					break;
        				}
        				else if ((b1-1 == ((1-2*(solution[i].second))*i)) && (solution[b2-1].first == 0) && (b2-1 == 1-2*(solution[b2-1].second)*b2)){ 
					// if the first switch is wrong, and the second switch is wrong, swap current and end loop
          					solution[i].second = !solution[i].second;
          					break;
          				}
        				else if ((b1-1 == ((1-2*(solution[i].second))*i)) && (b2-1 == (2*(solution[b2-1].second)*b2)-1)){ 
					// if the first switch is wrong, and the second switch is right, keep going. Dont need this line but its here for refrence
          
     		   			}
      
      					else if ((b1-1 == ((2*(solution[i].second))*i)-1)){ 
					// if the first switch is right, keep going. Dont need this line but its here for refrence
          
          
          				}
      				}
  	
    			}
  		}
	}
}
