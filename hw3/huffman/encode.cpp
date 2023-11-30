//hw3 babyyyyyyyyyyyyyyy!

//huffman encoding

#include<iostream>
#include<fstream>
#include<map>

using namespace std;

//custom structures
struct symbol{
	int frequency;
	string encoding;
	char letter;
};

int main(int argc, char *argv[]){
	string filename = argv[1];
	fstream in;
	int total_symbols = 0;
	map<char, symbol> symbol_map;

	//input
	struct symbol curr_symbol;
	char curr_char;
	in.open(filename.c_str()); //TODO: assert
	while(in >> curr_char){
		//in >> curr_char;
		total_symbols++;
		auto it = symbol_map.find(curr_char);
		if(it == symbol_map.end()){
			cout << "hit A on " << curr_char << endl;
			curr_symbol = {1, "", curr_char};
			symbol_map[curr_char] = curr_symbol;
			cout << symbol_map[curr_char].frequency <<endl;
		}
		else{
			cout << "hit B on " << curr_char << endl;
			symbol_map[curr_char].frequency++;
			cout << symbol_map[curr_char].frequency <<endl;
		}
	}

	for(auto it = symbol_map.begin(); it != symbol_map.end(); it++){
			//it->second.frequency /= total_symbols;
			cout << it->first << " has a frequency of " << it->second.frequency << endl;
	}
	return 0;
}
