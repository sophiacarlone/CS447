//now onto jabber and wocky

#include<iostream>
#include<fstream>
#include<bitset>

using namespace std;

int main(int argc, char *argv[]){
	string input= argv[1];
	string output= argv[2];
	ifstream in;
    ofstream out;
    in.open(input);
    out.open(output);

    char curr;
    while(in >> noskipws >> curr){
        bitset<8> b((int)curr); //convent number into bit array
        out << b;
    } 
    in.close();
    out.close();
}