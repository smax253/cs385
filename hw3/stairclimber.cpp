/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : 
 * Date        : 
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      :
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    auto result = vector<vector<int>>();
    if (num_stairs<=0) {
        result.push_back(vector<int>());
        return result;
    }
    for(int i = 1; i<4; i++){
        vector<vector<int>> ways = get_ways(num_stairs-i);
        for(auto it = ways.begin(); it != ways.end(); ++it){
            it->push_back(i);
            result.push_back(*it);
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
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    size_t maxsize = ways.size();
    int numdigits = num_digits(maxsize);
    cout<<setfill(" ");
    for (size_t i = 0; i<maxsize; i++){
        vector<int> current = ways[i];
        cout<<setw(numdigits)<<(i+1)<<". [";
        for(auto it = current.cbegin(); it != current.cend(); ++it){
            
        }
    }
}

int main(int argc, char * const argv[]) {

}
