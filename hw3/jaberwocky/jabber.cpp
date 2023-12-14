//now onto jabber and wocky

#include<iostream>
#include<fstream>
#include<map>
#include<stdlib.h>
#include<bitset>
#include<string>
#include<cmath>

using namespace std;

int length(int index);
string indexRep(int index, int len);

int main(int argc, char *argv[]){
	string input= argv[1];
	string output= argv[2];
	ifstream in;
    ofstream out;
    in.open(input);
    out.open(output);

	map<string, pair<int, int>> index_string_table;
	int index = 0;
	index_string_table[""] = {index, 0}; //first line of table {index, length}
	index++;

	string prefix = "";
	char curr;
	string curr_string = "";
	int len;
	while(in >> curr){
		curr_string += curr;
		auto it = index_string_table.find(curr_string);
		if(it == index_string_table.end()){
			len = length(index); //length
			index_string_table[curr_string] = {index, len};
			out << indexRep(index, len) << curr;
			cout << curr_string << endl;
			index++;
			curr_string = "";
		}
	}
	in.close();
	out.close();
}

int length(int index){
	int answer = log2 (index) + 1;
	return answer;
}

string indexRep(int index, int len){
	bitset<8> b(index);
	string result = b.to_string();
	return result.substr(result.size() - len);
}

	// the input is a sequence of bits.
	// it maintains a stretchy (resizable) table T of patterns.
	// 	initially, T contains a single pattern (empty string) at index 0.
	// it maintains a running counter of bit-length W.
	// 	initially, W = 0.
	// while there are more bits in the input stream:
	// 	find the longest pattern x in T matching that is a prefix of the input.
	// 	say T[k] = x.
	// 	let the next input bit after x be b.
	// 	output index k in W bits followed by b.
	// 	add pattern x.b to the table T at the next available index.
	// 	increment W if need be (#items in T is a power of two)
	// end