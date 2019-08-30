#include <iostream>

using namespace std;

int main(){
    int x = 5, y=6, *z = &x;
    // '*' declares a pointer, and dereferences a pointer
    // '&' -> address of operator
    cout << *z << endl;
    cout << "x = " << x << ", y = " << y << endl;
    return 0;
}