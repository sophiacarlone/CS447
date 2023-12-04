#include<iostream>
#include <fstream>
#include<vector>

using namespace std;

int main(){

    double pxx; // prob of staying on x if x was last thrown
    double pxy; // prob changing to y if x was last thrown
    double pyy;  // prob staying y if y was last thrown
    double pyx;  // prob changing to x if y was last thrown
    double xh;   // probability of getting heads if throwing x
    double xt;   // probability getting tails when throwing x
    double yh;   // probability of getting heads when throwing y
    double yt;   // probability of getting tails when throwing y
    string fname1,fname2, fname3, fname4;
    double prob, probX, probY, actX, actY; // total probability, probability of coin x being the last coin flipped, probability of coin y being the last coin flipped
    double sum;  // used in debugging,  prob x + prob y has to be 1, but it is not in all cases (hence the need for debugging)
    vector <bool> result, observed; //result vector (0 is X 1 is Y) observed vector (0 is T, 1 is H)
    bool x;

    cout << "Filename 1:" << endl;
    cin >> fname1;
    ifstream in;
    in.open(fname1);
    in >> pxx >> pyx >> pxy >> pyy;
    in.close();
    in.clear();

    cout << "Filename 2:" << endl;
    cin >> fname2;
    in.open(fname2);
    in >> xh >> yh;
    xt = 1 - xh;
    yt = 1 - yh;
    in.close();
    in.clear();

    cout << "Filename 3:" << endl;
    cin >> fname3;
    in.open(fname3);
   
    while (in >> x) {
        observed.push_back(x);
    }

    //first coin calculations.   

    if (observed[0] == 0){
        prob = .5*(xt + yt); // if a tails is observed, the total possibility is .5(xt) + .5(yt)
        probX = (.5*xt)/prob; // of the total probabiltiy .5(probability of tails given x) is the chance that coin x was flipped
        probY = (.5*yt)/prob; // of the total probabiltiy .5(probability of tails given y) is the chance that coin y was flipped

        if (probX > probY)
            result.push_back(0); // if there is a higher probability of coin x being the one that was flipped, we put a 0 to represent that in the result vector
        else
            result.push_back(1); // if there is a higher probability of coin y being the one that was flipped, we put a 1 to represent that in the result vector
    }

    else 
        prob = .5*(xh + yh);  // if a heads is observed, the total possibility is .5(xh) + .5(yh)
        probX = (.5*xh)/prob; // of the total probability .5(probability of heads given x) is the chance that coin x was flipped
        probY = (.5*yh)/prob; // of the total probability .5(probability of heads given y) is the chance that coin y was flipped

        if (probX > probY)
            result.push_back(0); // if there is a higher probability of coin x being the one that was flipped, we put a 0 to represent that in the result vector
        else
            result.push_back(1); // if there is a higher probability of coin y being the one that was flipped, we put a 1 to represent that in the result vector

    //rest of calculations

    for( int i = 1; i < observed.size(); i++){ //make this while (input isn't empty) for real code

        if (observed[i] == 0){

    
            probX = ((probX*pxx*xt)+(probY*pyx*xt)); //if tails is observed, the chance of flipped coin being x is: (prob that last was x)(prob stays x)(prob tails w/ x) +
            // prob that last was y)(prob changes to x)(prob tails w/ x) all divided by total probabilty

            probY = ((probX*pxy*yt)+(probY*pyy*yt)); // if tails is observed, the chance of flipped coin being y is: (prob that last was x)(prob changes to y)(prob tails w/ y) +
            //(prob that last was y)(prob stays y)(prob tails w/ y) all divided by total probability

            prob = probX + probY; 

            actX = probX/prob;
            actY = probY/prob;

            if (actX > actY){
                result.push_back(0); // if there is a higher probability of coin x being the one that was flipped, we put a 0 to represent that in the result vector
            }

            else{
                result.push_back(1); // if there is a higher probability of coin y being the one that was flipped, we put a 1 to represent that in the result vector
            }
        }

        else{
            probX = ((probX*pxx*xh)+(probY*pyx*xh));//if heads is observed, the chance of flipped coin being x is: (prob that last was x)(prob stays x)(prob heads w/ x) +
            // prob that last was y)(prob changes to x)(prob heads w/ x) all divided by total probability

            probY = ((probX*pxy*yh)+(probY*pyy*yh));// if heads is observed, the chance of flipped coin being y is: (prob that last was x)(prob changes to y)(prob heads w/ y) +
            //(prob that last was y)(prob stays y)(prob heads w/ y) all divided by total probability
            prob = probX + probY; 

            actX = probX/prob;
            actY = probY/prob;

            if (actX > actY){
                result.push_back(0); // if there is a higher probability of coin x being the one that was flipped, we put a 0 to represent that in the result vector
            }
            else{
                result.push_back(1); // if there is a higher probability of coin y being the one that was flipped, we put a 1 to represent that in the result vector
            }
        }   
    }
    cout << "Output File:" << endl;
    cin >> fname4;
   ofstream out;
   out.open(fname4);
   for(int i = 0; i < result.size(); i++){
    out << result[i] << " ";
   }
    return 0;
}
