/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Max Shi
 * Date        : Sep 9, 2019
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <string>
#include <iostream>
#include <sstream>


using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // displays the primes using correct spacing for each row
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    
    if (num_primes_<primes_per_row){
        for(int i = 2; i<limit_+1; i++){
            if(is_prime_[i]){
                if (i == 2){
                    cout << i;
                }else{
                    cout << " " << i;
                }
            }
        }
    }
    else{
        cout << setfill(' ');
        int rowcounter = 0;
        for(int i = 2; i<limit_+1; i++){
            if(is_prime_[i]){
                if(rowcounter >= primes_per_row){
                    cout<< endl;
                    cout << setw(max_prime_width) << i;
                    rowcounter = 1;
                }else if (rowcounter == 0){
                    cout << setw(max_prime_width) << i;
                    rowcounter += 1;
                }
                else{
                    cout << setw(max_prime_width+1) << i;
                    rowcounter += 1;
                }
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // Counts the number of primes calculated in the sieve
    int counter = 0;
    for(int i = 2; i<limit_+1; i++){
        if (is_prime_[i]){
            counter += 1;
        }
    }
    return counter;
}

void PrimesSieve::sieve() {
    // Uses Eratosthenes's Sieve to calculate primes
    for(int i = 0; i<limit_+1; i++){
        is_prime_[i] = true;
    }
    for (int i = 2; i<=sqrt(limit_+1); i++){
        if (is_prime_[i]){
            for (int j = i*i; j<limit_+1; j+=i){
                
                if(i<sqrt(2147483647)) {
                    is_prime_[j] = false;
                }
            }
            
            //cout<<"done: " << i << endl;
        }
    }
    int index = limit_;
    while(index>0 && max_prime_ == 0){
        if (is_prime_[index]) max_prime_ = index;
        index--;
    }
    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    //Finds the number of digits in a given integer num.
    int counter = 0;
    while(num>0){
        num /= 10;
        counter++;
    }
    return counter;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }
    
    //produce desired output from the limit input
    //initialize sieve
    PrimesSieve sieve(limit);
    //print number of primes
    cout << endl << "Number of primes found: " << sieve.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    sieve.display_primes();
    return 0;
}
