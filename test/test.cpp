#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* const argv[]) {
    vector<pair<int,int>> vec(10);
    pair<int,int> test(0,0);
    cout << (test == vec[0]) << endl;
    return 0;
}
