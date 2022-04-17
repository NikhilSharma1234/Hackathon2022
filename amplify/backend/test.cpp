//g++ test.cpp -lboost_system -lboost_filesystem -o email

#define BOOST_NO_CXX11_SCOPED_ENUMS
#include <boost/filesystem.hpp>
#undef BOOST_NO_CXX11_SCOPED_ENUMS
#include <iostream>
#include <string>
#include <vector>

using std::cout; using std::endl;
using std::string; using std::vector;
using namespace boost::filesystem;

void getFiles(vector<string>& files);

int main(){
    vector<string> files;
    getFiles(files);
    for(int i=0; i < files.size(); i++){
        cout << files[i] << endl;
    }
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