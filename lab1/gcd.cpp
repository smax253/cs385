/*******************************************************************************
 * Name    : gcd.cpp
 * Author  : Max Shi
 * Version : 1.0
 * Date    : August 29, 2019
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;

int gcd_recursive(int m, int n){
    if (n<0) return gcd_recursive(m,n*-1);
    if(n==0) return m;
    else if(n>m) return gcd_recursive(n,m);
    else{
        int mod = m%n;
        return gcd_recursive(n,mod);
    }
}

int gcd_iterative(int m, int n){
    if (n<0) n *= -1;
    if (m<0) m *= -1;
    while(n!=0){
        if(n>m) {
            int temp = m;
            m = n;
            n = temp;
        }
        else{
            int mod = m%n;
            m = n;
            n = mod;
        }
    }
    return m;
}

int main(int argc, char* const argv[]){
    int m, n;
    istringstream iss;

    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>"
             << endl;
        return 1;
    }
    iss.str(argv[1]);
    if ( !(iss >> m) ) {
        cerr << "Error: The first argument is not a valid integer."
             << endl;
        return 1;
    }
    iss.clear(); // clear the error code
    iss.str(argv[2]);
    if ( !(iss >> n) ) {
        cerr << "Error: The second argument is not a valid integer."
             << endl;
        return 1;
    }
    cout << "Iterative: gcd(" << m << ", " << n << ") = " << gcd_iterative(m,n) << endl;
    cout << "Recursive: gcd(" << m << ", " << n << ") = " << gcd_recursive(m,n) << endl; 
}