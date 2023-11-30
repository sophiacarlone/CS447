#include<iostream>
#include<vector>

using namespace std;

class node{ //may make this a struct 
    private:
        string symbols;
        int value;
}

class tree{
    private:
        node* root_node;
        vector<node*> subtrees;
    public:
        //print
}