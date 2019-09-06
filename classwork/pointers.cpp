#include <iostream>

using namespace std;

void display_array(int array[], const int length){
    cout << "[";
    if (length > 0){
        cout << array[0];
    }
    for (int i = 1; i<length; i++){
        cout << ", " << array[i];
    }
    cout << "]" << endl;
}

void display_array_ptr(int array[] , const int length){
    cout << "[";
    for (int *ptr = array, *end = array+length; ptr<end; ++ptr){
        if(ptr != array){
            cout << ", ";
        }
        cout << *ptr;
    }
    cout << "]" << endl;
}

void pass_by_value(int x){
    x = 10;
}

void pass_by_pointer(int *x){
    *x = 10;
}

void pass_by_reference(int &x){
    x = 10;
}

int main(){
    int x = 5, y=6, *z = &x;
    // '*' declares a pointer, and dereferences a pointer
    // '&' -> address of operator
    cout << *z << endl;
    cout << "x = " << x << ", y = " << y << endl;
    *z = 7;
    cout << "x = " << x << ", y = " << y << endl;
    z = &y;
    *z = 7;
    cout << "x = " << x << ", y = " << y << endl;
    
    //cout << ++z << endl; //uh oh
    //cout << *z << endl; //oops

    //z += 30000; //yikes
    //*z = 30;    //I did it again, first segfault of many --- use gdb to debug!

    int *values = new int[y];
    for (int i = 0; i<y; ++i){
        values[i] = i;
    }//use valgrind for checking memory leaks
    display_array(values, y);
    display_array_ptr(values, y);
    delete [] values; //free up memory
    
    x = 5;
    pass_by_reference(x);
    cout << "x = " << x << endl;
    return 0;
}