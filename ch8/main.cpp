#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

int main() {

    vector<string> text;
    ifstream fs("../test.txt", ios_base::in);
    if (fs) {
        string line = "";
        while (getline(fs, line)) {
            text.push_back(line);
        }
    } else {
        cerr << "counld't open file: test.txt" << endl; 
    }

    for (auto s : text) {
        cout << s << "\n";
    }


}