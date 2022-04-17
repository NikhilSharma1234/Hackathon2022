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

//add words that are associated with spam
void addWords(map<string, int>& SpamWords, map<string, int>& neutralWords, vector<string>& potentialFlags, string filename);

//fill maps with words from text file
void fillMap(map<string, int>& flagWords, string filename);

//iterate through potential flags and add to SpamWords
void forRealThisTime(map<string, int> SpamWords, vector<string>& potentialFlags);

//get the file names from inbox
void getFiles(vector<string>& files);

//return the sender  in the filename
string getSender(string filename);

//mark sender in spamSenders.txt
void markSender(string sender);

//read the email and return the percent of spam associated words
double readEmail(map<string, int>& flagWords, map<string, int>& neutralWords, string& filename, string & sender);

int main() {
    system("python3.9 my_scripts.py");
    //set the percentage of spam words to mark as spam
    int threshhold = 1;
    //set the maps for the word sets
    map<string, int> Spamwords;
    map<string, int> neutralWords;
    map<string, int> spamSenders;
    vector<string> potentialFlags;
    fillMap(spamSenders, "spamSenders.txt");
    fillMap(Spamwords, "flagwords.txt");
    fillMap(neutralWords, "neutralwords.txt");
    
    //get the filenames for all of the emails
    vector<string> files;
    getFiles(files);
    
    //declare variables that will be used in for
    double percentage;
    string sender;
    //map<string, int>:: iterator var;
    
    

    for(int i = 0; i < files.size(); i++){
        sender = getSender(files[i]);

        if(spamSenders.count(sender) > 0){

            //call function to add bad words on this email
        }
        else{
            percentage = readEmail(Spamwords, neutralWords, files[i], sender);
            
            if(percentage >= threshhold){
                cout << "Your email from " << sender << " has been marked as spam." << endl; 
                markSender(sender);
                spamSenders.insert(pair<string, int> (sender, 1)); //add sender to map of spamsenders
                
                addWords(Spamwords, neutralWords, potentialFlags, files[i]);//call read bademail function
                forRealThisTime(Spamwords, potentialFlags);
                system("python3.9 move.py");
                system("python3.9 uploadToS3.py");
            }
        }
    }
   
    //system("python3.9 my_scripts.py");
    return 0;
}

void addWords(map<string, int>& SpamWords, map<string, int>& neutralWords, vector<string>& potentialFlags, string filename){
    ifstream file;
    file.open (filename);
    if (!file.is_open()) return;

    string sub;
    while (file >> sub)
    {
        if(neutralWords.count(sub) > 0 || SpamWords.count(sub) > 0 || count(potentialFlags.begin(), potentialFlags.end(), sub) > 0){
        }
        // else if(potentialFlags.count(sub) > 0){
            
        // }
        else{
            potentialFlags.push_back(sub);
        }
    }
    // string sender, email, line;
    // int count = 0;
    
    // ifstream myfile(filename);
    // if (myfile.fail()) {
    //     cout << "could not open file" << endl;
    //     exit(1);
    // }
    // getline(myfile, sender, '<');
    // getline(myfile, email);
    // email.pop_back();
    // myfile >> line;
    
    // while (!myfile.eof()) {
    
    // //myfile.get(); // get blank space
    // getline(myfile, line);
    //  //cout << "from email " << line << endl;
    // int len = line.size();
    //     while(len > 0) { // identify all individual strings
        
    //     len = line.find(" ");
    //         if (len > 0) {
    //             sub = line.substr(0, len);
    //             line = line.substr(len + 1, line.size());
    //             cout << "in if" << endl;
    //             cout << sub << " " << count << endl;
    //             count++;
    //         }
    //         else {
    //             sub = line;
    //             cout << "in else" << endl;
    //             cout << sub << " " << count << endl;
    //             count++;
    //         }
    //         // if(neutralWords.count(sub) > 0 || SpamWords.count(sub) > 0){
    //         // }
    
    //         // if(potentialFlags.count(sub) > 0){
    //         //     potentialFlags[sub]++;
    //         // }
    //         // else{
    //         //     potentialFlags.insert(pair<string, int>(sub, 1));
    //         // }
                 
    //     }
    // myfile.close();
    //}
}
    // for ( const auto &myPair : potentialFlags ) {
    //     SpamWords.insert(pair<string, int>(myPair.first, 1));
    //     ofstream myfile;
    //     myfile.open ("flagwords.txt", std::ios_base::app);
    //     myfile << myPair.first << "\n";
    //     myfile.close();
    // }

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

void forRealThisTime(map<string, int> SpamWords, vector<string>& potentialFlags){
    ofstream myfile;
    myfile.open ("flagwords.txt", std::ios_base::app);
    
    
    for(int i = 0; i < potentialFlags.size(); i++){
        myfile << potentialFlags[i] << "\n";
    }
   myfile.close();
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

string getSender(string filename){
    string sender;
    ifstream myfile(filename);
    if (myfile.fail()) {
        cout << "could not open file" << endl;
        exit(1);
    }
    getline(myfile, sender, '<');
    getline(myfile, sender);
    sender.pop_back();
    return sender;
}


void markSender(string sender){
    ofstream myfile;
    myfile.open ("spamSenders.txt", std::ios_base::app);
    myfile << sender << "\n";
    myfile.close();
}

double readEmail(map<string, int>& flagWords, map<string, int>& neutralWords, string& filename, string & email){
    string name, line, sender;
    double count = 0;
    double total = 0;
    hash<string> hash_string;
    

    ifstream myfile(filename);
    if (myfile.fail()) {
        cout << "could not open file" << endl;
        exit(1);
    }
    getline(myfile, sender, '<');
    getline(myfile, email);
    email.pop_back();
    myfile >> line;
    
    while (!myfile.eof()) {
    
    myfile.get(); // get blank space
    getline(myfile, line);
     //cout << "from email " << line << endl;
    int len = line.size();
        while(len > 0) { // identify all individual strings
        string sub;
        len = line.find(" ");
            if (len > 0) {
                sub = line.substr(0, len);
                line = line.substr(len + 1, line.size());
                total++;
            }
            else {
                sub = line;
                total++;
            }
            // myfile >> line;
            // total ++;
             if(flagWords.count(sub) > 0){
                 count++;
                 
             }
             else {
             }
                

        }  
    }
    

    return (count / total) * 100.0;
}