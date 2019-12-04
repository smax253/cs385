/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Max Shi and Constance Xu
 * Version     : 1.0
 * Date        : 11/30/2019
 * Description : Calculates the shortest paths given a file with vertices.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>

using namespace std;
struct Edge{
    string from, to;
    long long int weight;
    int fromIndex, toIndex;
    Edge(string _from, string _to, int _weight) : from(_from), to(_to), weight(_weight){
        fromIndex = _from[0]-'A';
        toIndex = _to[0]-'A';
    }
};

int num_digits(long long int num) {
    //Finds the number of digits in a given integer num.
    int counter = 0;
    while(num>0){
        num /= 10;
        counter++;
    }
    return counter;
}
vector<char> findPath(vector<vector<string>> intermediates, int start, int end){
    vector<char> output;
    char startchar = 'A' + start;
    char endchar = 'A' + end;
    if (start == end) {
        output.push_back(startchar);
    }
    else{
        char intermediate = intermediates[start][end][0];
        int intIndex = intermediate - 'A';
        if (intermediate == '-') {
            output.push_back(startchar);
            output.push_back(endchar);
        }
        else{
            output = findPath(intermediates, start, intIndex);
            vector<char> addition = findPath(intermediates, intIndex, end);
            for(size_t i = 1; i<addition.size(); i++){
                output.push_back(addition[i]);
            }
        }
    }
    return output;
}

void printPaths(vector<vector<long long int>> distMatrix, vector<vector<long long int>> minWeights, vector<vector<string>> intermediates, unsigned int max_vertices, int max_distance){
    long long int max_weight = 0;
    for(unsigned int i = 0; i<max_vertices; i++){
        for(unsigned int j = 0; j<max_vertices; j++){
            if(minWeights[i][j]>max_weight) max_weight = minWeights[i][j];
        }
    }
    //cout<<max_distance<<endl;
    int numdigits = num_digits(max_distance);
    if (max_distance == 0) numdigits = 1;
    //cout<<numdigits<<endl;
    cout<<setfill(' ');
    cout<<"Distance matrix:\n ";
    for(unsigned int i = 0; i<max_vertices; i++){
        char current = 'A' + i;
        cout<<setw(numdigits+1)<<current;
    }
    cout<<endl;
    for(unsigned int i = 0; i<max_vertices; i++){
        char current = 'A' + i;
        cout<<current;
        for(unsigned int j = 0; j<max_vertices; j++){
            if(distMatrix[i][j] == -1) cout<<setw(numdigits+1)<<"-";
            else cout<<setw(numdigits+1)<<distMatrix[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    //cout<<max_weight<<endl;
    numdigits = num_digits(max_weight);
    if (max_weight == 0) numdigits = 1;
    //cout<<numdigits<<endl;
    cout<<"Path lengths:\n ";
    for(unsigned int i = 0; i<max_vertices; i++){
        char current = 'A' + i;
        cout<<setw(numdigits+1)<<current;
    }
    cout<<endl;
    for(unsigned int i = 0; i<max_vertices; i++){
        char current = 'A' + i;
        cout<<current;
        for(unsigned int j = 0; j<max_vertices; j++){
            if(minWeights[i][j] == -1) cout<<setw(numdigits+1)<<"-";
            else cout<<setw(numdigits+1)<<minWeights[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    numdigits = 1;
    cout<<"Intermediate vertices:\n ";
    for(unsigned int i = 0; i<max_vertices; i++){
        char current = 'A' + i;
        cout<<setw(numdigits+1)<<current;
    }
    cout<<endl;
    for(unsigned int i = 0; i<max_vertices; i++){
        char current = 'A' + i;
        cout<<current;
        for(unsigned int j = 0; j<max_vertices; j++){
            cout<<setw(numdigits+1)<<intermediates[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    for(size_t i = 0; i<max_vertices; i++){
        for (size_t j = 0; j<max_vertices; j++){
            char from = i+'A';
            char to = j+'A';
            if(minWeights[i][j] == -1){
                cout<<from<<" -> "<<to<<", distance: infinity, path: none\n";
            }
            else{
                cout<<from<<" -> "<<to<<", distance: "<<minWeights[i][j]<<", path: ";
                stringstream path;
                vector<char> pathChars = findPath(intermediates, i, j);
                auto it = pathChars.cbegin();
                for(auto end = pathChars.cend(); it != end-1; ++it){
                    path<<*it<<" -> ";
                }
                path<<*it;
                cout<<path.str()<<endl;
            }
        }
    }
    
}

void shortestPaths(vector<Edge> edges, unsigned int max_vertices){
    vector<vector<long long int>> distMatrix;
    vector<vector<long long int>> minWeights;
    vector<vector<string>> intermediates;
    int max_distance = 0;
    for(unsigned int i = 0; i<max_vertices; i++){
        distMatrix.push_back(vector<long long int>(max_vertices,-1));
        minWeights.push_back(vector<long long int>(max_vertices,-1));
        intermediates.push_back(vector<string>(max_vertices,"-"));
        minWeights[i][i] = 0;
        distMatrix[i][i] = 0;
    }
    for(auto it = edges.begin(), end = edges.end(); it != end; ++it){
        minWeights[it->fromIndex][it->toIndex] = it->weight;
        distMatrix[it->fromIndex][it->toIndex] = it->weight;
        if (it->weight>max_distance) max_distance = it->weight;
    }
    for(size_t k = 0; k<max_vertices; k++){
        for(size_t i = 0; i<max_vertices; i++){
            for (size_t j = 0; j<max_vertices; j++){
                if(minWeights[i][k] != -1 && minWeights[k][j] != -1){
                    long long int pathlength = minWeights[i][k] + minWeights[k][j];
                    if(minWeights[i][j] == -1 || minWeights[i][j]>pathlength) {
                        minWeights[i][j] = pathlength;
                        intermediates[i][j] = 'A' + k;
                    }
                }
            }
        }
    }
    printPaths(distMatrix, minWeights, intermediates, max_vertices, max_distance);
}




int main(int argc, char *argv[]){
    vector<Edge> edges;
    
    int buffer;
    unsigned int numvertices = 0;
    string maxChar;
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
            istringstream iss(line);
            if(line_number == 1){
                if(iss>>buffer){
                    if(buffer>26 || buffer<=0){
                        cerr<<"Error: Invalid number of vertices \'"<<line<<"\' on line "<<line_number<<".\n";
                        return 1;
                    }
                    else{
                        numvertices = buffer;
                        
                        maxChar = ('A' + numvertices-1);
                        //cout<<maxChar<<endl;
                    }
                }
                else{
                    cerr<<"Error: Invalid number of vertices \'"<<line<<"\' on line "<<line_number<<".\n";
                    return 1;
                }
            }else{
                vector<string> tokens{istream_iterator<string>{iss},
                      istream_iterator<string>{}};
                if(tokens.size() != 3){
                    cerr<<"Error: Invalid edge data \'"<<line<<"\' on line "<<line_number<<".\n";
                    return 1;
                }
                else{
                    if(tokens[0]<"A" || tokens[0] > maxChar){
                        cerr<<"Error: Starting vertex \'"<<tokens[0]<<"\' on line "<<line_number<<" is not among valid values A-"+maxChar+".\n";
                        return 1;
                    }
                    if (tokens[1]<"A" || tokens[1] > maxChar){
                        cerr<<"Error: Ending vertex \'"<<tokens[1]<<"\' on line "<<line_number<<" is not among valid values A-"+maxChar+".\n";
                        return 1;//same vertex??
                    }
                    istringstream vweight(tokens[2]);
                    int weight;
                    if(vweight >> weight){
                        if (weight<=0){
                            cerr<<"Error: Invalid edge weight \'"<<tokens[2]<<"\' on line "<<line_number<<".\n";
                            return 1;
                        }
                    }else{
                        cerr<<"Error: Invalid edge weight \'"<<tokens[2]<<"\' on line "<<line_number<<".\n";
                        return 1;
                    }
                    edges.push_back(Edge(tokens[0], tokens[1], weight));
                }
            }
            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    shortestPaths(edges, numvertices);
    /*
    for(auto it = edges.cbegin(); it != edges.cend(); ++it){
        cout<<it->fromIndex<<" "<<it->toIndex<<" "<<it->weight<<endl;
    }*/
    return 0;
}