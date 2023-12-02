#include<iostream>
#include<vector>

using namespace std;

struct node{  
    string symbols;
    int value;
};
/*
class tree{
    private:
        struct node* root_node;
        tree subtrees[2]; //should at max be 2 for this problem
        bool children;
        //subtrees[0] = right, subtrees[1] = left and make traversion easier
        int size; //TODO determine size
    public:
        //void tree2array();
        void print();
};

//*string tree::tree2array(){
    // string treearray[size];
    // treearray[0] = root_node->symbols;
    // if(children){
    //     treearray[1] = subtrees[0]->symbols;
    //     treearray[2] = subtrees[1]->symbols;
    // }
//
//}

void tree::print(){

}
*/