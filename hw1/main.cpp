//Sophia Carlone

#include<iostream>
//#include<vector>
#include<cstdlib> //exit
#include<cmath> //abs()
//#include<type_traits> //is_integer

using namespace std;

void print(int array[], int size);

#define S2B 2 //switches two each bulb config

int main(){
	int bulbs;
	int switches;

	cout << "how many switches" << endl;
	cin >> switches;
	cout << "how many bulbs" << endl;
	cin >> bulbs;

	//int switch_configs[2]; //switch configuration of the bulbs
	//vector<switch_configs> bulb_configs; //the bulbs and their own configurations
	
	int bulb_configs[S2B*bulbs];

	cout << "insert the configs" << endl;	

	int temp = 0;
	for(int i = 0; i < bulbs; i++){
		cin >> temp;
		if(abs(temp) > switches) exit(1); //TODO: add number checking (can use ascii)
		bulb_configs[S2B*i] = temp;
		cin >> temp;
		if(abs(temp) > switches) exit(1);
		bulb_configs[(S2B*i)+1] = temp;
	}
	
	print(bulb_configs, S2B*bulbs);		

}

void print(int array[], int size){
	for(int i = 0; i < size; i++){
		cout << array[i] << " ";
	}
	cout << endl;
}
