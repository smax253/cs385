/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Max Shi
 * Date        : 9/25/2019
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // Returns a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    auto result = vector<vector<int>>();
    if (num_stairs<=0) {
        result.push_back(vector<int>());
        return result;
    }
    for(int i = 1; i<4; i++){
        if(num_stairs>=i){
            vector<vector<int>> ways = get_ways(num_stairs-i);
            for(vector<int> step : ways){
                step.insert(step.begin(),i);
                result.push_back(step);
            }
        }
    }
    return result;

}

int num_digits(size_t num) {
    //Finds the number of digits in a given integer num.
    int counter = 0;
    while(num>0){
        num /= 10;
        counter++;
    }
    return counter;
}

void display_ways(const vector< vector<int> > &ways) {
    // Displays the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    size_t maxsize = ways.size();
    int numdigits = num_digits(maxsize);
    cout << setfill(' ');
    for (size_t i = 0; i<maxsize; i++){
        vector<int> current = ways[i];
        cout<<setw(numdigits)<<(i+1)<<". [";
        for(size_t j = 0; j<current.size()-1; j++){
            cout << current[j] <<", ";
        }
        cout<<current[current.size()-1]<<"]"<<endl;
    }
}

int main(int argc, char * const argv[]) {
    if(argc!=2){
        cerr << "Usage: " << argv[0] << " <number of stairs>"
             << endl;
        return 1; 
    }
    int limit;
    string test = argv[1];
    istringstream iss(test);
    if(!(iss>>limit) || limit<=0){
        cerr << "Error: Number of stairs must be a positive integer."
             << endl;
        return 1; 
    }
    vector<vector<int>> ways = get_ways(limit);
    //cout<<"ways done"<<endl;
    if (limit>1) cout<<ways.size()<<" ways to climb "<<limit<<" stairs."<<endl;
    else cout<<ways.size()<<" way to climb "<<limit<<" stair."<<endl;
    display_ways(ways);
    return 0;
}
