#include<iostream>
#include<vector>

using namespace std;

int main(){

    double pxx = .75; // prob of staying on x if x was last thrown
    double pxy = .25; // prob changing to y if x was last thrown
    double pyy = .1;  // prob staying y if y was last thrown
    double pyx = .9;  // prob changing y if y was last thrown
    double xh = .6;   // probability of getting heads if throwing x
    double xt = .4;   // probability getting tails when throwing x
    double yh = .8;   // probability of getting heads when throwing y
    double yt = .2;   // probability of getting tails when throwing y
    double prob, probX, probY; // total probability, probability of coin x being the last coin flipped, probability of coin y being the last coin flipped


    double sum;  // used in debugging,  prob x + prob y has to be 1, but it is not in all cases (hence the need for debuggung)


   
    double observed[20]; //observed vector (0 is T, 1 is H, array for testing, will be vector when getting from file)
    
    vector <double> result;//result vector (0 is X 1 is Y)
    for (int i = 0; i< 20; i++){
    observed[i]= (rand()%2); //randomly filling it
    }


    //first coin calculations
    

    if (observed[0] == 0){
        prob = .5*(xt + yt); // if a tails is observed, the total possibility is .5(xt) + .5(yt)
        probX = (.5*xt)/prob; // of the total probabiltiy .5(probability of tails given x) is the chance that coin x was flipped
        probY = (.5*yt)/prob; // of the total probabiltiy .5(probability of tails given y) is the chance that coin y was flipped

        sum = probX + probY;   //debug line
        cout << probX << " first " << probY << " sum " << sum << endl; //debug line

        if (probX > probY)
            result.push_back(0); // if there is a higher probability of coin x being the one that was flipped, we put a 0 to represent that in the result vector
        else
            result.push_back(1); // if there is a higher probability of coin y being the one that was flipped, we put a 1 to represent that in the result vector
    }


    else 
        prob = .5*(xh + yh);  // if a heads is observed, the total possibility is .5(xh) + .5(yh)
        probX = (.5*xh)/prob; // of the total probabiltiy .5(probability of heads given x) is the chance that coin x was flipped
        probY = (.5*yh)/prob; // of the total probabiltiy .5(probability of heads given y) is the chance that coin y was flipped

        sum = probX + probY; //debug line
        cout << probX << " first " << probY << " sum " << sum << endl; //debug line

        if (probX > probY)
            result.push_back(0); // if there is a higher probability of coin x being the one that was flipped, we put a 0 to represent that in the result vector
        else
            result.push_back(1); // if there is a higher probability of coin y being the one that was flipped, we put a 1 to represent that in the result vector



    //rest of calculations
    


    for( int i = 1; i < 20; i++){ //make this while (input isn't empty) for real code

        if (observed[i] == 0){

            prob = (probX*pxx*xt + probX*pxy*yt + probY*pyy*yt + probY*pyx*xt); //if a tails is observed, the total probability is:  (prob that last was x)(prob stays x)(prob tails w/ x) +
 // (prob that last was x)(prob changes to y)(prob tails w/ y) + (prob that last was y)(prob stays y)(prob tails w/ y) + (prob that last was y)(prob changes to x)(prob tails w/ x)

            probX = ((probX*pxx*xt)+(probY*pyx*xt))/prob; //if tails is observed, the chance of flipped coin being x is: (prob that last was x)(prob stays x)(prob tails w/ x) +
            // prob that last was y)(prob changes to x)(prob tails w/ x) all divided by total probabilty

            probY = ((probX*pxy*yt)+(probY*pyy*yt))/prob; // if tails is observed, the chance of flipped coin being y is: (prob that last was x)(prob changes to y)(prob tails w/ y) +
            //(prob that last was y)(prob stays y)(prob tails w/ y) all divided by total probabilty

            sum = probX + probY; //debug line

            if (probX > probY){
                cout << probX << "  " << probY << " sum " << sum << endl; //debug line
                result.push_back(0); // if there is a higher probability of coin x being the one that was flipped, we put a 0 to represent that in the result vector
            }

            else{
                 cout << probX << "  " << probY << " sum " << sum << endl;//debug line
                result.push_back(1); // if there is a higher probability of coin y being the one that was flipped, we put a 1 to represent that in the result vector
            }
        }

        else{
            prob = (probX*pxx*xh + probX*pxy*yh + probY*pyy*yh + probY*pyx*xh);//if a heads is observed, the total probability is:  (prob that last was x)(prob stays x)(prob heads w/ x) +
 // (prob that last was x)(prob changes to y)(prob heads w/ y) + (prob that last was y)(prob stays y)(prob heads w/ y) + (prob that last was y)(prob changes to x)(prob heads w/ x)

            probX = ((probX*pxx*xh)+(probY*pyx*xh))/prob;//if heads is observed, the chance of flipped coin being x is: (prob that last was x)(prob stays x)(prob heads w/ x) +
            // prob that last was y)(prob changes to x)(prob heads w/ x) all divided by total probabilty

            probY = ((probX*pxy*yh)+(probY*pyy*yh))/prob;// if heads is observed, the chance of flipped coin being y is: (prob that last was x)(prob changes to y)(prob heads w/ y) +
            //(prob that last was y)(prob stays y)(prob heads w/ y) all divided by total probabilty

            sum = probX + probY;  //debug line
            if (probX > probY){
                 cout << probX << "  " << probY << " sum " << sum << endl; //debug line
                result.push_back(0); // if there is a higher probability of coin x being the one that was flipped, we put a 0 to represent that in the result vector
            }
            else{
                 cout << probX << "  " << probY << " sum " << sum << endl; //debug line
                result.push_back(1); // if there is a higher probability of coin y being the one that was flipped, we put a 1 to represent that in the result vector
            }
        }   
    }
     for( int i = 0; i < 20; i++){    //debug line
        cout << observed[i] << endl;  //debug line
    }
    cout << "halfway" << endl;        //debug line
    for( int i = 0; i < 20; i++){     //debug line
        cout << result.at(i) << endl; //debug line
    }
    return 0;
}