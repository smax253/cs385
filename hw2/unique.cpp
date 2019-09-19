/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Max Shi
 * Date        : 9/17/2019
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    for(auto it = s.cbegin(); it != s.cend(); ++it){
        int diff = *it-'a';
        if(diff<0 || diff>25) return false;
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    unsigned int storage = 0;
    for(size_t i = 0; i<s.size(); i++){
        unsigned int diff = 1;
        diff<<=(s.at(i)-'a');
        if ((diff&storage) != 0) return false;
        else storage |= diff;
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc!=2){
        cerr << "Usage: " << argv[0] << " <string>"
             << endl;
        return 1; 
    }
    string test = argv[1];
    if(!is_all_lowercase(test)){
        cerr << "Error: String must contain only lowercase letters."
             << endl;
        return 1; 
    }
    if(all_unique_letters(test)){
        cout << "All letters are unique." << endl;
    }
    else{
        cout << "Duplicate letters found." << endl;
    }
    return 0;
}
