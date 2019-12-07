/*******************************************************************************
 * Name        : anagramfinder.cpp
 * Author      : Max Shi
 * Date        : 11/15/2019
 * Description : Determines the strings with largets number of anagrams in an input file.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


string stringCountingSort(const string &input){
    vector<int> chars(26);
    string result;
    for(char c : input){
        int current = c - 'a';
        int capitalcurrent = c - 'A';
        if (current<26 && current >=0) chars[current]++;
        else if (capitalcurrent<26 && capitalcurrent>=0) chars[capitalcurrent]++;
        else return input;
    }
    
    result.reserve(input.size());
    for(size_t i = 0; i<chars.size(); i++){
        for(int j = 0; j<chars[i]; j++){
            result.append(1, (char)(i+'a'));
        }
    }
    return result;
}

vector<vector<string>> findAnagrams(const vector<string> &inputs, unsigned int &maxAnagrams){
    
    multimap<string, string> table;
    vector<string> maxKeys;
    for(auto it = inputs.cbegin(), end = inputs.cend(); it != end; ++it){
        string sorted = stringCountingSort(*it);
        if(sorted.size()>0){
            unsigned int currentAnagrams = table.count(sorted);
            if (currentAnagrams){
                table.emplace(pair<string, string>(sorted, *it));
                ++currentAnagrams;
                if (currentAnagrams > maxAnagrams){
                    maxKeys.clear();
                    maxKeys.emplace_back(sorted);
                    maxAnagrams = currentAnagrams;
                }else if(currentAnagrams == maxAnagrams){
                    maxKeys.emplace_back(sorted);
                }
            }else{
                table.emplace(pair<string, string>(sorted, *it));
            }
        }
    } 
    vector<vector<string>> anagrams;
    
    for (auto it = maxKeys.cbegin(), end = maxKeys.cend(); it != end; ++it){
        vector<string> addAnagrams;
        for (auto anaitr = table.lower_bound(*it), anaend = table.upper_bound(*it); anaitr != anaend; ++anaitr){
            addAnagrams.emplace_back(anaitr->second);
        }
        anagrams.emplace_back(addAnagrams);
    }
    
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
            if (word.size() <= 30)
                allWords->emplace_back(word);
        }
        dictFile.close();
    }
    size_t totalSize = allWords->size();
    if (totalSize == 0) {
        cerr<<"Error: File \'"<<argv[1]<<"\' not found.";
        return 1;
    }
    
    vector<vector<string>> splitLengths;
    splitLengths.reserve(31);
    vector<double> distributions = {0.0001,0.001, 0.002, 0.02, 0.04, 0.065, 0.1, 0.15, 0.15, 0.15, 0.15, 0.15, 0.1, 0.08, 0.05, 0.03, 0.03, 0.015, 0.006};
    
    for(size_t i = 0; i<31; i++){
        vector<string> toAdd;
        if (i<distributions.size()){
            toAdd.reserve((int)(totalSize*distributions[i]));
        }
        else{
            toAdd.reserve((int)(0.003*totalSize));
        }
        splitLengths.emplace_back(toAdd);
    }
    for(auto it = allWords->cbegin(); it != allWords->cend(); ++it){
        splitLengths[it->size()].emplace_back(*it);
    }
    
    vector<vector<string>> maxanagrams; 
    unsigned int maxnumber = 2;
    for(size_t k = 1; k<splitLengths.size(); k++){
        if (splitLengths[k].size() > 0){
            unsigned int prevnumber = maxnumber;
            vector<vector<string>> anagrams = findAnagrams(splitLengths[k], maxnumber);
            if (prevnumber != maxnumber) maxanagrams = anagrams;
            else{
                maxanagrams.insert(maxanagrams.end(), anagrams.begin(), anagrams.end());
            }
        }
    }
    if(maxanagrams.size() == 0) cout<<"No anagrams found.\n";
    else{
        cout<<"Max anagrams: " << maxnumber<<"\n";
        map<string, size_t> indexes;
        vector<string> firsts;
        for(size_t i = 0; i<maxanagrams.size(); i++){
            sort(maxanagrams[i].begin(), maxanagrams[i].end());
            firsts.emplace_back(maxanagrams[i][0]);
            indexes.insert(pair<string, size_t>(maxanagrams[i][0], i));
        }
        sort(firsts.begin(), firsts.end());
        for(size_t i = 0; i<firsts.size(); i++){
            vector<string> toPrint = maxanagrams[indexes[firsts[i]]];
            for (size_t j = 0; j<toPrint.size(); j++){
                cout<<toPrint[j]<<"\n";
            }
            cout<<"\n";
        }
    } 
    delete allWords;
    return 0;
}