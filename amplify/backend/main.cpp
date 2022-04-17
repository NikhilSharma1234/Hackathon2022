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

//get the file names from inbox
void getFiles(vector<string>& files);

//put all of the words into an array
//void parseFile(map<string, int>& words) ;

double readEmail(map<string, int>& flagWords, map<string, int>& neutralWords, map<string, int>& potentialFlags, string& filename, string & sender);

void addWords(map<string, int>& sWords, map<string, int>& words);

void fillMap(map<string, int>& flagWords, string filename);

void markSender(string sender);

int main() {
    int threshhold = 1;
    map<string, int> Spamwords;
    map<string, int> neutralWords;
    map<string, int> spamSenders;
    map<string, int> potentialFlags;
    
    fillMap(spamSenders, "spamSenders.txt");
    fillMap(Spamwords, "flagwords.txt");
    fillMap(neutralWords, "neutralwords.txt");
    
    vector<string> files;
    getFiles(files);
    //double wordCount = 0;
    //double totalWord = 0;
    double percentage;
    string sender, filename;
    ofstream SenderList;
    //map<string, int>:: iterator var;
    //string words[1000];
    
    
    
    // getFiles(files);
    // parseFile(Spamwords);
    //parseFile(words);

    for(int i = 0; i < files.size(); i++){
        
        if(1 == 0){
            //call function to add bad words on this email
        }
        else{
            percentage = readEmail(Spamwords, neutralWords, potentialFlags, files[i], sender);
            
            if(percentage >= threshhold){
            cout << "Your email from " << sender << " has a spam word percentage of " << percentage << "%" << endl;
               
                markSender(sender);
                spamSenders.insert(pair<string, int> (sender, 1)); //add sender to map of spamsenders
            
            
            //call read bademail function
            }
        }
        cout << sender << endl;
        
    }
   
    
   
    
    
    

    
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

void markSender(string sender){
    ofstream myfile;
    myfile.open ("spamSenders.txt", std::ios_base::app);
    myfile << sender << "\n";
    myfile.close();
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

// void parseFile(map<string, int>& words){
    
//     string name, line, fileName;
//     int score;
//     hash<string> hash_string;

    
    
//     ifstream myfile("flagwords.txt");
//     if (myfile.fail()) {
//         cout << "could not open file" << endl;
//         exit(1);
//     }
   
//     while (!myfile.eof()) {
//     //myfile >> score; // get score
//     //myfile.get(); // get blank space
//     getline(myfile, line);
// cout << line << endl;
//     int len = line.size();
//         while(len > 0) { // identify all individual strings
//         string sub;
//         len = line.find(" ");
//             if (len > 0) {
//                 sub = line.substr(0, len);
//                 line = line.substr(len + 1, line.size());
//             }
//             else {
//                 sub = line.substr(0, line.size() - 1);
//             }
//          words[hash_string(sub)] = sub;// insert string with the score
    
//         //cout << hash_string(sub) << endl;
//         }
//     }
        
// }

double readEmail(map<string, int>& flagWords, map<string, int>& neutralWords, map<string, int>& potentialFlags, string& filename, string & email){
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
    
    while (!myfile.eof()) {
    
    //myfile.get(); // get blank space
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
             if(flagWords.count(sub) > 0){
                 count++;
                    // if(neutralWords[sub] || flagWords[sub]){}
    
                    // else if(flagWords[sub]){}
    
                    // else if(potentialFlags[sub]){
                    //     potentialFlags[sub]++;
                    // }
    
                    // else{
                    //     potentialFlags.insert(pair<string, int>(sub, 1));
                    // }   
                 
             }
             else {
             }

        }
    }
    
    cout << "sender is " << sender << endl;
    return (count / total) * 100.0;
}

void addWords(map<string, int>& sWords, map<string, int>& words){
    //neutral word map
    //bad word map
    //file name
    //
    //https://stackoverflow.com/questions/1443793/iterate-keys-in-a-c-map
    // for ( const auto &myPair : newFlagWords ) {
    //      flagWords.insert(<string, int>(myPari.first, 1));
    // }
}

