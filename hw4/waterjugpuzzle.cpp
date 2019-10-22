/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Max Shi
 * Date        : 10/5/2019
 * Description : Solves and prints the output to the solution of a given water jug puzzle.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>
#include <stack>
using namespace std;
// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
    bool equals(State other){
        return a == other.a && b == other.b && c == other.c;
    }
    int sum(){
        return a+b+c;
    }
    static string pair_to_string(pair<int, int> elem, int cap){
        State current(elem.first, elem.second, cap-elem.first-elem.second);
        return current.to_string();
    }
};

void link_and_queue(State current, State next, queue<State> &store, vector<vector<pair<int,int>>> &link){
    //Take a potential next step and store it in queue and link in array only if not visited before
    if(link[next.a][next.b] == pair<int,int>(-1,-1)){
        link[next.a][next.b] = pair<int,int>(current.a, current.b);
        store.push(next);
    }
}

void pour_buckets(State current, State capacity, State goal, queue<State> &store, vector<vector<pair<int,int>>> &link){
    //Pour each bucket if possible in the given order in the problem
    if(current.equals(goal)) return;
    if(current.a != capacity.a && current.c != 0){
        int pour = min(capacity.a - current.a, current.c);
        State next(current.a + pour, current.b, current.c - pour);
        link_and_queue(current, next, store, link);
    }
    if(current.a != capacity.a && current.b != 0){
        int pour = min(capacity.a - current.a, current.b);
        State next(current.a + pour, current.b - pour, current.c);
        link_and_queue(current, next, store, link);
    }
    if(current.b != capacity.b && current.c != 0){
        int pour = min(capacity.b - current.b, current.c);
        State next(current.a, current.b + pour, current.c - pour);
        link_and_queue(current, next, store, link);
    }
    if(current.b != capacity.b && current.a != 0){
        int pour = min(capacity.b - current.b, current.a);
        State next(current.a - pour, current.b + pour, current.c);
        link_and_queue(current, next, store, link);
    }
    if(current.c != capacity.c && current.b != 0){
        int pour = min(capacity.c - current.c, current.b);
        State next(current.a, current.b-pour, current.c+pour);
        link_and_queue(current, next, store, link);
    }
    if(current.c != capacity.c && current.a != 0){
        int pour = min(capacity.c - current.c, current.a);
        State next(current.a - pour, current.b, current.c+pour);
        link_and_queue(current, next, store, link);
    }
}

const void printSolution(State goal, vector<vector<pair<int,int>>> &link){
    //Print solution to the problem
    pair<int, int> current(0,0);
    pair<int, int> end(goal.a, goal.b);
    int totalcap = goal.sum();
    stack<pair<int, int>> trace;
    trace.push(end);
    while(end != current){
        end = link[end.first][end.second];
        trace.push(end);
    }
    pair<int, int> prev = trace.top();
    cout<< "Initial state. " << State::pair_to_string(prev, totalcap) << endl;
    trace.pop();
    while(!trace.empty()){
        int pouramt;
        string plural = " gallons ";
        char origin, dest;
        pair<int, int> current = trace.top();
        if(current.first < prev.first) {
            origin = 'A';
            pouramt = prev.first-current.first;
        }
        else if (current.second < prev.second) {
            origin = 'B';
            pouramt = prev.second - current.second;
        }
        else origin = 'C';
        if(current.first > prev.first) dest = 'A';
        else if (current.second > prev.second) dest = 'B';
        else dest = 'C';
        if(origin == 'C'){
            if(dest == 'A') pouramt = current.first - prev.first;
            if(dest == 'B') pouramt = current.second - prev.second;
        }
        if (pouramt == 1) plural = " gallon ";
        cout<<"Pour "<<pouramt<<plural<<"from "<<origin<<" to "<< dest << ". "<<State::pair_to_string(current,totalcap)<<endl;
        prev = current;
        trace.pop();
    }
}

void solve(State capacity, State goal){
    //Solve the bucket problem
    vector<vector<pair<int,int>>> link;
    for(int i = 0; i<=capacity.a; i++){
        link.push_back(vector<pair<int,int>>());
        for(int j = 0; j<=capacity.b; j++){
            link[i].push_back(pair<int,int>(-1,-1));
        }
    }
    State current(0, 0, capacity.c);
    queue<State> store;
    store.push(current);
    while(!store.empty() && !current.equals(goal)){
        pour_buckets(current, capacity, goal, store, link);
        current = store.front();
        store.pop();
    }
    if (current.equals(goal)){
        printSolution(goal, link);
    }
    else{
        cout<<"No solution."<<endl;
    }
}

int main(int argc, char * const argv[]) {
    if (argc != 7){     //check number of arguments
        cerr << "Usage: " << argv[0] << " <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"
             << endl;
        return 1; 
    }
    vector<int> inputs;
    istringstream iss;
    for (int i = 1; i<7; i++){ //parse arguments and store in vector, throw error if invalid
        iss.str(argv[i]);
        int current;
        if(!(iss>>current) || (i<4 && current == 0) || current<0){
            char jug = 'A'+(i-1)%3;
            string type = i<4?"capacity":"goal";
            cerr << "Error: Invalid "<<type<< " \'"<<argv[i]<<"\' for jug " << jug<<"."<< endl;
            return 1;
        }
        inputs.push_back(current);
        iss.clear();
    }
    for (size_t i = 0; i<3; i++){  
        if(inputs[i] < inputs[i+3]){
            char jug = 'A'+i%3;
            cerr << "Error: Goal cannot exceed capacity of jug "<<jug<<"."<<endl;
            return 1;
        }
    }
    State cap(inputs[0], inputs[1], inputs[2]);
    State goal(inputs[3],inputs[4],inputs[5]);
    if(cap.c != goal.sum()){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." <<endl;
        return 1;
    }
    solve(cap, goal);
    return 0;
}