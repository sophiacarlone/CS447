//now onto jabber and wocky

#include<iostream>
#include<fstream>
#include<map>
#include<stdlib.h>
#include<bitset>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

int length(int index);
string indexRep(int index, int len);
int string2int(string s);

int main(int argc, char *argv[]){
	string input= argv[1];
	string output= argv[2];
	ifstream in;
    ofstream out;
    in.open(input);
    out.open(output);

	map<int, pair<string, int>> index_string_table;
	int index = 0;
	int maxlen = 0;
	index_string_table[index] = {"", maxlen}; //first line of table {string, length}
	index++;

	string curr_string = "";
	char curr;
	string curr_index = "";
	int len;
    while(!in.eof()){
        cout << "hit" << endl;
        for(int i = 0; i < maxlen; i++){
            cout << "hit A" << endl;
            in >> curr;
            if(in.eof()){
                cout << "hit end " << curr_index << endl;
                curr = '\0';
                continue;
            }
            cout << "current for number " << curr << endl;
            curr_index += curr;
        }
        in >> curr;
        cout << "current " << curr << endl;
        cout << "index found " << string2int(curr_index) << endl;
        auto it = index_string_table.find(string2int(curr_index));
        if(curr == '\0') curr_string =  it->second.first;
        else curr_string =  it->second.first + curr;;
        cout << "string " << curr_string << endl;
        out << curr_string;
        maxlen = length(index);
        index_string_table[index] = {curr_string, maxlen};
        index++;
        curr_index = "";
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

int string2int(string s){
    int number = 0;
    //cout << "string: " << s << endl;
    reverse(s.begin(), s.end());
    // char curr;
    for(int i = 0; i < s.size(); i++){
        if(s[i] == '1') number += pow(2, i);
        // cout << "number " << number << endl;
    }
    return number;
}