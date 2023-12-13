//now onto jabber and wocky

#include<iostream>
#include<fstream>
#include<bitset>
#include<cmath>

using namespace std;

int main(int argc, char *argv[]){
	string input= argv[1];
	string output= argv[2];
	ifstream in;
    ofstream out;
    in.open(input);
    out.open(output);

    char curr; //byte
    int number = 0;
    while(!in.eof()){
        for(int i = 7; i >= 0; i--){
             in >> noskipws >> curr;
            if(curr == '1') number += pow(2, i);
        }
        if(number != 0) out << (char)number;
        number = 0;
    } 
    in.close();
    out.close();
}