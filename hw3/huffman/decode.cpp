#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(int argc, char *argv[]){
	string encodedFile = argv[1];
	string treeFile = argv[2];
	ifstream inE; //e for encoded
	ifstream inT; //t for tree
    inE.open(encodedFile);
    inT.open(treeFile);
    ofstream out;
    out.open("decoded_output.txt");

    vector<string> tree; 

    string curr_symbol;
    while(inT >> curr_symbol){
        tree.push_back(curr_symbol);
    }

    char curr; //can make this a bool but this makes more sense to me
    int index = 0;
    int next_index = 0;

    while(inE >> curr){
        // cout << "top" << endl;
        // cout <<"index " <<  index << endl;
        // cout <<"next index " <<  next_index << endl;
        int next_index = 0;
        if(curr == '1'){
            index = (index * 2) + 2;
            next_index = (index * 2) + 2;
        }
        else{ 
            index = (index * 2) + 1;
            next_index = (index * 2) + 1;
        }
        // cout << "below" << endl;
        // cout <<"index " <<  index << endl;
        // cout <<"next index " <<  next_index << endl;
        if( next_index > tree.size()-1) { //found a letter
            // cout << "In here" << endl;
            // cout << tree[index];
            out << tree[index];
            index = 0;
            next_index = 0;
        } 
        else if( tree[next_index] == "-" ) { //found a letter
            // cout << "In here" << endl;
            // cout << tree[index];
            out << tree[index];
            index = 0;
            next_index = 0;
        }
        //index = next_index; 
    }
    out.close();
}