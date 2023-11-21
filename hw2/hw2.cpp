#include<iostream>
#include<vector>

using namespace std;

int main(){

    double pxx = .75;
    double pxy = .25;
    double pyy = .1;
    double pyx = .9;
    double xh = .6;
    double xt = .4;
    double yh = .8;
    double yt = .2;
    double sum;

    //observed vector (0 is T, 1 is H, arr for testing)
    double observed[20];
    //result vector (0 is X 1 is Y)
    vector <double> result;
    for (int i = 0; i< 20; i++){
    observed[i]= (rand()%2);
    }
    //first coin calculations
    double prob, probX, probY;

    if (observed[0] == 0){
        prob = .5*(xt + yt);
        probX = (.5*xt)/prob;
        probY = (.5*yt)/prob;
        sum = probX + probY;
        cout << probX << " first " << probY << " sum " << sum << endl;
        if (probX > probY)
            result.push_back(0);
        else
            result.push_back(1);
    }
    else 
        prob = .5*(xh + yh);
        probX = (.5*xh)/prob;
        probY = (.5*yh)/prob;
        sum = probX + probY;
        cout << probX << " first " << probY << " sum " << sum << endl;
        if (probX > probY)
            result.push_back(0);
        else
            result.push_back(1);

    //rest of calculations
    
    for( int i = 1; i < 20; i++){ //make this while input isn't empty for real code
        if (observed[i] == 0){
            prob = (probX*pxx*xt + probX*pxy*yt + probY*pyy*yt + probY*pyx*xt);
            probX = ((probX*pxx*xt)+(probY*pyx*xt))/prob;
            probY = ((probX*pxy*yt)+(probY*pyy*yt))/prob;
            sum = probX + probY;

            if (probX > probY){
                cout << probX << "  " << probY << " sum " << sum << endl;
                result.push_back(0);
            }

            else{
                 cout << probX << "  " << probY << " sum " << sum << endl;
                result.push_back(1);
            }
        }

        else{
            prob = (probX*pxx*xh + probX*pxy*yh + probY*pyy*yh + probY*pyx*xh);
            probX = ((probX*pxx*xh)+(probY*pyx*xh))/prob;
            probY = ((probX*pxy*yh)+(probY*pyy*yh))/prob;
            sum = probX + probY;

            if (probX > probY){
                 cout << probX << "  " << probY << " sum " << sum << endl;
                result.push_back(0);
            }

            else{
                 cout << probX << "  " << probY << " sum " << sum << endl;
                result.push_back(1);
            }
        }   
    }
     for( int i = 0; i < 20; i++){
        cout << observed[i] << endl;
    }
    cout << "halfway" << endl;
    for( int i = 0; i < 20; i++){
        cout << result.at(i) << endl;
    }
    return 0;
}