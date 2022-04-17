#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
using std::cout; using std::cin;
using std::endl; using std::string;
using std::map; using std::copy;
using std::ifstream; using std::hash;
 using namespace boost::filesystem;
//read the txt file

//create hash table for the no no words

//check the email for the no no words

//if the email has too many no no words, mark it as spam

//

//get the file names from inbox
void getFiles(vector<string>& files);

//put all of the words into an array
void parseFile(map<int, string>& words) ;

string readEmail(map<int, string>& sWords, map<int, string>& words, int& count);



int main() {
    vector<string> files;
    getFiles(files);
    int wordCount = 0;
    string sender;
    map<int, string>:: iterator var;
    //string words[1000];
    map<int, string> Spamwords;
    map<int, string> words;
    
    
    // getFiles(files);
    parseFile(Spamwords);
    //parseFile(words);
    sender = readEmail(Spamwords, words, wordCount);
    //cout << "Name: " << sender << " spam word count: " << wordCount << endl;
    
    

    
    //system("python3.9 my_scripts.py");
    return 0;
}

void getFiles(vector<string>& files){
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
}

void parseFile(map<int, string>& words){
    
    string name, line;
    int score;
    hash<string> hash_string;
    // cout << "Input a file name: ";
    // cin >> name;
    ifstream myfile("text.txt");
    if (myfile.fail()) {
        cout << "could not open file" << endl;
        exit(1);
    }
   
    while (!myfile.eof()) {
    myfile >> score; // get score
    myfile.get(); // get blank space
    getline(myfile, line);
    int len = line.size();
        while(len > 0) { // identify all individual strings
        string sub;
        len = line.find(" ");
            if (len > 0) {
                sub = line.substr(0, len);
                line = line.substr(len + 1, line.size());
            }
            else {
                sub = line.substr(0, line.size() - 1);
            }
         words[hash_string(sub)] = sub;// insert string with the score
    
        //cout << hash_string(sub) << endl;
        }
    }
}

string readEmail(map<int, string>& sWords, map<int, string>& words, int& count){
    string name, line, sender, email;
    count = 0;
    hash<string> hash_string;
    // cout << "Input a file name: ";
    // cin >> name;
    ifstream myfile("tester.txt");
    if (myfile.fail()) {
        cout << "could not open file" << endl;
        exit(1);
    }
    getline(myfile, sender, '<');
    getline(myfile, email);
    cout << sender << " " << email << endl;
   email.erase(email.end());
    while (!myfile.eof()) {
    
    myfile.get(); // get blank space
    getline(myfile, line);
    int len = line.size();
        while(len > 0) { // identify all individual strings
        string sub;
        len = line.find(" ");
            if (len > 0) {
                sub = line.substr(0, len);
                line = line.substr(len + 1, line.size());
            }
            else {
                sub = line;
            }
            if(sWords.count(hash_string(sub)) > 0){
                count++;
            }
            else {
                sWords[hash_string(sub)] = sub;
            }
            if(words.count(hash_string(sub)) > 0){
                
            }
            else {
                words[hash_string(sub)] = sub;
            }
        }
    }
    return email;
}