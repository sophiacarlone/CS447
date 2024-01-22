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
	int maxlen = 0;
	index_string_table[""] = {index, maxlen}; //first line of table {index, length}
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
			out << indexRep(index_string_table.find(prefix)->second.first, maxlen) << curr;
			if(len > maxlen) maxlen = len;
			index++;
			curr_string = "";
		}
		else{
			prefix = curr_string;
		}
	}
	if(prefix != ""){
		out << 	indexRep(index_string_table.find(prefix)->second.first, maxlen);
	}
	in.close();
	out.close();
}

int length(int index){
	int answer = log2 (index) + 1;
	return answer;
}

string indexRep(int index, int len){
	bitset<64> b(index);
	string result = b.to_string();
	return result.substr(result.size() - len);
}
