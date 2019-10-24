/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Max Shi
 * Version     : 1.0
 * Date        : 10/21/2019
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long counter = 0;
    for (int i = 0; i<length; i++){
        int value = array[i];
        for(int j = i+1; j<length; j++){
            if (array[j]<value) counter++;
        }
    }
    return counter;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    vector<int> scratch(length);
    return mergesort( array, &scratch[0], 0, length-1);
    // Hint: Use mergesort!
}

static long mergesort(int array[], int scratch[], int low, int high) {
    if(low<high){
        int mid = low+(high-low)/2;
        //cout<<mid<<endl;
        long inversion_counter = 0;
        inversion_counter += mergesort(array, scratch, low, mid);
        inversion_counter += mergesort(array, scratch, mid+1, high);
        int L = low;
        int H = mid+1;
        for(int i = low; i<=high; i++){
            if (L<=mid && (H > high || array[L] <= array[H])){
                scratch[i] = array[L];
                L++;
            }
            else{
                scratch[i] = array[H];
                H++;
                inversion_counter += H-i-1;
                //cout<< H-i-1<< endl;
            }
        }
        for(int i = low; i<=high; i++){
            array[i] = scratch[i];
        }
        return inversion_counter;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    bool slow = false;
    if(argc > 2){
        cerr << "Usage: " << argv[0] << " [slow]"<<endl;
        return 1;
    }else if (argc == 2){
        if(string("slow").compare(argv[1])==0) slow = true;
        else {
            cerr << "Error: Unrecognized option \'"<<argv[1]<<"\'."<<endl;
            return 1;
        }
    }
    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }
    if(values.size() == 0){
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    
    // TODO: produce output
    cout<<"Number of inversions: "<<(slow ?count_inversions_slow(&values[0], values.size()) :count_inversions_fast(&values[0], values.size()))<<endl;
    
    return 0;
}
