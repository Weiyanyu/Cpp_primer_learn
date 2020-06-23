#include "../lib/basicInclude.h"


using namespace std;

string::size_type find_char(const string &s, char c, string::size_type &occurs);
void errorMsg(initializer_list<string> il);

int main() {
    string::size_type ctr = 0;
    errorMsg({"aaa", "bbb", "ccc", "ddd"});
}

string::size_type find_char(const string &s, char c, string::size_type &occurs) {
    occurs = 0;
    
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return i;
        }
    }
    return -1;
}

void errorMsg(initializer_list<string> il) {
    for (auto it = il.begin(); it != il.end(); it++) {
        cout << *it << " ";
    }

    cout << endl;
}