/*******************************************************************************
 * Name        : anagramfinder.cpp
 * Author      : Max Shi
 * Date        : 9/17/2019
 * Description : Determines the strings with largets number of anagrams in an input stream.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <thread>
#include <utility>
#include <future>
using namespace std;

string stringCountingSort(string input){
    vector<int> chars(26);
    string result;
    for(size_t i = 0; i<input.size(); i++){
        int current = input[i] - 'a';
        int capitalcurrent = input[i] - 'A';
        if (current<26 && current >=0) chars[current]++;
        else if (capitalcurrent<26 && capitalcurrent>=0) chars[capitalcurrent]++;
        else return input;
    }
    
    result.reserve(input.size());
    for(size_t i = 0; i<chars.size(); i++){
        for(int j = 0; j<chars[i]; j++){
            result.push_back((char)(i+'a'));
        }
    }
    return result;
}

vector<vector<string>> findAnagrams(vector<string> inputs){
    
    map<string, vector<string>> table;
    for(auto it = inputs.cbegin(); it != inputs.cend(); ++it){
        string sorted = stringCountingSort(*it);
        if(sorted.size()<=0) continue;
        if (table.count(sorted)){
            table[sorted].push_back(*it);
        }else{
            //cout<<*it<<endl;
            vector<string> toInsert;
            toInsert.push_back(*it);
            table.insert(pair<string, vector<string>>(sorted, toInsert));
        }
    }
    vector<vector<string>> anagrams;
    
    unsigned int maxanagrams = 2;
    
    for (auto it = table.cbegin(); it != table.cend(); ++it){
        vector<string> current = it->second;
        if (current.size() > maxanagrams){
            //cout<<anagrams.size()<<endl;
            maxanagrams = current.size();
            anagrams.clear();
            anagrams.push_back(current);
        }
        else if (current.size() == maxanagrams){
            anagrams.push_back(current);
        }
    }
    
    table.clear();
    //cout<<"finish"<<endl;
    return anagrams;
}

int main(int argc, char * const argv[]) {
    // Reads and parses command line arguments.
    // Calls other functions to produce correct output.
    if(argc!=2){
        cerr << "Usage: " << argv[0] << " <dictionary file>"
             << endl;
        return 1; 
    }
    vector<string> *allWords = new vector<string>();
    string word;
    ifstream dictFile;
    dictFile.open(argv[1]);
    if(dictFile.is_open()) {
        while(dictFile.good()) {
            getline(dictFile,word);
            allWords->push_back(word);
        }
        dictFile.close();
    }
    size_t totalSize = (*allWords).size();
    if (totalSize == 0) {
        cerr<<"Error: File \'"<<argv[1]<<"\' not found.";
        return 1;
    }
    //cout<<totalSize<<endl;
    vector<vector<string>> splitLengths;
    splitLengths.reserve(31);
    vector<double> distributions{0.001,0.01, 0.03, 0.055, 0.085, 0.13, 0.15, 0.15, 0.135, 0.105, 0.08, 0.055, 0.035, 0.025, 0.015, 0.01, 0.007};
    
    for(size_t i = 0; i<40; i++){
        vector<string> toAdd;
        if (i<distributions.size()){
            //cout<<(int)(totalSize*distributions[i])<<endl;
            toAdd.reserve((int)(totalSize*distributions[i]));
        }
        else{
            toAdd.reserve((int)(0.005*totalSize));
        }
        splitLengths.push_back(toAdd);
    }
    //cout<<splitLengths.size()<<endl;
    for(auto it = allWords->cbegin(); it != allWords->cend(); ++it){
        //cout<<*it<<endl;
        
        splitLengths[it->size()].push_back(*it);
    }
    delete allWords;
    //splitLengths.size()
    
    /*
    size_t k = 8;
    cout<<splitLengths[k].size()<<endl;
    if (splitLengths[k].size() > 0){
        vector<vector<string>> anagrams = findAnagrams(splitLengths[k]);
        for(size_t i = 0; i<anagrams.size(); i++){
            for(size_t j = 0; j<anagrams[i].size(); j++){
                vector<string> anas = anagrams[i];
                cout<<anas[j]<<endl;
            }
            cout<<endl;
        }
    }
    */
    vector<vector<string>> maxanagrams;
    unsigned int maxnumber = 2;
    for(size_t k = 1; k<splitLengths.size(); k++){
        //cout<<splitLengths[k].size()<<endl;
        if (splitLengths[k].size() > 0){
            vector<vector<string>> anagrams = findAnagrams(splitLengths[k]);
            for(size_t i = 0; i<anagrams.size(); i++){
                vector<string> anas = anagrams[i];
                if (anas.size() > maxnumber){
                    maxnumber = anas.size();
                    maxanagrams.clear();
                    maxanagrams.push_back(anas);
                }
                else if (anas.size() == maxnumber){
                    maxanagrams.push_back(anas);
                }
                
            }
        }
        //splitLengths[k].clear();
    }
    
    if(maxanagrams.size() == 0) cout<<"No anagrams found.";
    else{
        cout<<"Max anagrams: " << maxnumber<<endl;
        map<string, size_t> indexes;
        vector<string> firsts;
        for(size_t i = 0; i<maxanagrams.size(); i++){
            sort(maxanagrams[i].begin(), maxanagrams[i].end());
            firsts.push_back(maxanagrams[i][0]);
            indexes.insert(pair<string, size_t>(maxanagrams[i][0], i));
        }
        sort(firsts.begin(), firsts.end());
        for(size_t i = 0; i<firsts.size(); i++){
            vector<string> toPrint = maxanagrams[indexes[firsts[i]]];
            for (size_t j = 0; j<toPrint.size(); j++){
                cout<<toPrint[j]<<endl;
            }
            cout<<endl;
        }
    }
    
   
    //cout<<stringCountingSort("hello");
    goto cleanup;
    cleanup:
    
    return 0;
}