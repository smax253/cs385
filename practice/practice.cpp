#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

size_t lomuto_partition(int array[], size_t left, size_t right) {
    int pivot = array[left];
    size_t pivotindex = left;
    for (size_t i = left+1; i<=right; ++i){
        if (array[i] < pivot){
            pivotindex += 1;
            swap(array[pivotindex], array[i]);
        }
    }
    swap(array[left], array[pivotindex]);
    //cout<<pivotindex<<endl;
    for(size_t i = left; i<=right; i++){
        cout<<array[i]<<" ";
    }
    cout<<endl;
    return pivotindex;
}


int main(int argc, char* const argv[]) {
    //int m, n;
    //istringstream iss;
    //int array[14] = {55, 6 ,2 ,4 ,768, 1, 4 ,567 ,123 ,65, 12 ,345, 12 ,-100};
    //cout<<lomuto_partition(array, 0, 13)<<endl;
    int array1[3] = {6,7,10};
    cout<<array1[0]<<endl;
    for(size_t i = 0; i<3; i++){
        cout<<array1[i]<<" ";
    }
    cout<<endl;
    cout<<lomuto_partition(array1, 0, 2)<<endl;
    for(size_t i = 0; i<3; i++){
        cout<<array1[i]<<" ";
    }
    cout<<endl;
    /*
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

    cout << "m is " << m << endl;
    cout << "n is " << n << endl;
    cout << "max(" << m << ", " << n << ") is " << max(m, n) << endl;
    */
    return 0;
}
