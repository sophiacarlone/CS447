#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

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

void contradiction(){
}


int main(){
	vector<pair<int,int>> configuration = lightbulbs("3.txt");
	int bulbs, switches;
	bulbs = configuration.front().first;
	switches = configuration.front().second;

	pair <bool,bool> solution[switches];
	for (int i = 0; i< switches; i++){
  		solution[i].first = 0;
  		solution[i].second = (rand()%2);
	}


	//input contradiction logic here and set first to 1 if we dont want to edit that switch anymore

	int x = 0;
	while (x == 0){
 		for (int i = 0; i< switches; i++){
			if(solution[i].first = 0){
            			for (int j = 1; j < bulbs + 1; j++){
                    			if (solution[i].second == 1){
                              			if (configuration[j].first == -(i+1))
                                            		solution[i].second = 0;
                    			}
            			}
      			}      
  		}
	}
}
                                                                    
