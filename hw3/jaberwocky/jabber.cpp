//now onto jabber and wocky

#include<iostream>
#include<fstream>
#include<map>
#include<stdlib.h>

using namespace std;

int main(int argc, char *argv[]){
	string input= argv[1];
	string output= argv[2];
	ifstream in;
    ofstream out;
    in.open(input);
    out.open(output);

	map<string, pair<int, int>> index_string_table;
	index_string_table[""] = {0, 0}; //first line of table

	while(!in.eof()){

	}
	in.close();
	out.close();
}

	the input is a sequence of bits.
	it maintains a stretchy (resizable) table T of patterns.
		initially, T contains a single pattern (empty string) at index 0.
	it maintains a running counter of bit-length W.
		initially, W = 0.
	while there are more bits in the input stream:
		find the longest pattern x in T matching that is a prefix of the input.
		say T[k] = x.
		let the next input bit after x be b.
		output index k in W bits followed by b.
		add pattern x.b to the table T at the next available index.
		increment W if need be (#items in T is a power of two)
	end