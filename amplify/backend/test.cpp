//g++ test.cpp -lboost_system -lboost_filesystem -o email

//"/Inbox" + filename

#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <fstream>
#include <bits/stdc++.h>

using std::cout; using std::endl;
using std::string; using std::vector;
using std::map; using std::pair;
using std::fstream; using std::ofstream;
using namespace boost::filesystem;

//void getFiles(vector<string>& files);

void fillMap(map<string, int>& flagWords, string filename);

void markSender(string sender);

int main(){
    map<string, int> newFlagWords;
    map<string, int> neutralWords;
    map<string, int> flagWords;
    string word = "lego";
    
    newFlagWords.insert(pair<string, int>(word, 1));
    
    if(neutralWords[word]){}
    
    else if(flagWords[word]){}
    
    else if(newFlagWords[word]){
        newFlagWords[word]++;
    }
    
    else{
        newFlagWords.insert(pair<string, int>(word, 1));
    }
    cout << newFlagWords["lego"] << endl;
    //map<string, int> flagWords;
    //flagWords.insert(pair<string, int>("free", 1));
    //fillMap(flagWords, "flagwords.txt");
    //cout << flagWords["lego"] << endl;
    //cout << findInMap(flagWords, "free", tester.txt) << endl;
    return 0;
    
}

void fillMap(map<string, int>& flagWords, string filename){
    fstream file;
    file.open(filename.c_str());
    string word;
  
    // extracting words from the file
    while (file >> word)
    {
        flagWords.insert(pair<string, int>(word, 1));
        
    }
    file.close();
}

void markSender(string sender){
    ofstream myfile;
    myfile.open ("spamSenders.txt");
    myfile << sender << "\n";
    myfile.close();
}

/*void getFiles(vector<string>& files){
    path p ("Inbox/");

    directory_iterator end_itr;

    // cycle through the directory
    for (directory_iterator itr(p); itr != end_itr; ++itr)
    {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            string current_file = itr->path().string();
            files.push_back(current_file);
        }
    }
}*/