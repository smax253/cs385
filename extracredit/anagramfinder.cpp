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

string stringCountingSort(const string &input){
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

void findAnagrams(vector<vector<vector<string>>> *result, vector<string> *inputs, bool *ready){
    auto stringCountingSort = [](string &input){
        vector<int> chars(26);
        string result;
        for(char c : input){
            int current = c - 'a';
            int capitalcurrent = c - 'A';
            if (current<26 && current >=0) chars[current]++;
            else if (capitalcurrent<26 && capitalcurrent>=0) chars[capitalcurrent]++;
            else return result;
        }
        result.reserve(input.size());
        for(size_t i = 0; i<chars.size(); i++){
            for(int j = 0; j<chars[i]; j++){
                result.push_back((char)(i+'a'));
            }
        }
        return result;
    };
    cout<<"ready"<<*ready<<endl;
    vector<string> maxKey;
    unsigned int maxanagrams = 2;
    map<string, vector<string>> table;
    size_t currSize = 0;
    bool threadReady = false;
    while(!(*ready) || !threadReady){
        size_t size = inputs->size();
        if (size == currSize || (*ready && inputs->size() == 0)) threadReady = true;
        else{
            threadReady = false;
            while (size > currSize){
                //cout<<inputs->size();
                string current = (*inputs)[currSize];
                //cout<<"HELP"<<endl;
                //cout<<current<<endl;
                string sorted = stringCountingSort(current);
                if (sorted.size() <= 0) {
                    ++currSize;
                    break;
                }
                else{
                    if (table.count(sorted)){
                        table[sorted].push_back(current);
                        vector<string> currentVec = table[sorted];
                        if (currentVec.size() > maxanagrams){
                            maxKey.clear();
                            maxanagrams = currentVec.size();
                            maxKey.push_back(sorted);
                        }else if (currentVec.size() == maxanagrams){
                            maxKey.push_back(sorted);
                        }
                    }
                    else{
                        vector<string> currentVec;
                        currentVec.push_back(current);
                        table.insert(pair<string, vector<string>>(sorted, currentVec));
                    }
                }
                ++currSize;
            }
        }
        //cout<<currSize<<endl;
        if(*ready && inputs->size()==currSize) cout<<"inputs: "<<size<<"current: "<<currSize<<endl;
    }
    
    cout<<"Array Size: " <<inputs->size()<<", Map size : "<<table.size()<<", Curr size : "<<currSize<<", Max anagrams: "<<maxanagrams<<", maxkey: "<<maxKey.size() <<endl;
    if (maxKey.size() == 0) return;
    //cout<<maxanagrams<<endl;
    
    vector<vector<string>> anagrams;
    
    for(size_t i = 0; i<maxKey.size(); i++){
        anagrams.push_back(table[maxKey[i]]);
    }
    
    table.clear();
    result->push_back(anagrams);
    
    cout<<"result pushed"<<endl;
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
    vector<vector<string>*> splitLengths;
    splitLengths.reserve(31);
    vector<double> distributions{0.001,0.01, 0.03, 0.055, 0.085, 0.13, 0.15, 0.15, 0.135, 0.105, 0.08, 0.055, 0.035, 0.025, 0.015, 0.01, 0.007};
    bool ready = false;
    for(size_t i = 0; i<40; i++){
        vector<string>* toAdd = new vector<string>();
        if (i<distributions.size()){
            //cout<<(int)(totalSize*distributions[i])<<endl;
            toAdd->reserve((int)(totalSize*distributions[i]));
        }
        else{
            toAdd->reserve((int)(0.005*totalSize));
        }
        splitLengths.push_back(toAdd);
    }
    //cout<<splitLengths.size()<<endl;
    vector<vector<vector<string>>> *results = new vector<vector<vector<string>>>();
    
    results->reserve(40);
    
    vector<thread> threadsvec;
    for(size_t i = 0; i<splitLengths.size(); i++){
        thread nextThread(findAnagrams, results, splitLengths[i], &ready);
        threadsvec.push_back(move(nextThread));
    }
    for(auto it = allWords->cbegin(); it != allWords->cend(); ++it){
        //cout<<*it<<endl;
        splitLengths[it->size()]->push_back(*it);
        //if(it->size() == 4) cout<<"added"<<endl;
    }
    //cout<<splitLengths[5]->size()<<endl;
    ready = true;
    //findAnagrams(results, splitLengths[5], &ready);
    delete allWords;
   
    //cout<<splitLengths[4]->size()<<endl;
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
    
    for(size_t k = 0; k<threadsvec.size(); k++){
        threadsvec[k].join();
    }
    cout<<"uhh"<<endl;
    
    for(size_t k = 0; k<results->size(); k++){
        //cout<<(*results)[k].size()<<endl;
        if ((*results)[k].size() > 0){
            vector<vector<string>> anagrams = (*results)[k];
            for(size_t i = 0; i<anagrams.size(); i++){
                vector<string> anas = anagrams[i];
                if (anas.size() > maxnumber){
                    maxnumber = anas.size();
                    maxanagrams = vector<vector<string>>();
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
    delete results;
    
    return 0;
}