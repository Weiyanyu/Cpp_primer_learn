#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <numeric>
#include <memory>


#include "blob.h"
#include "text.h"

using namespace std;

ostream& print(ostream &out, const QueryResult &result);
void runQueries(const string &filename);

int main() {

    runQueries("/home/weiyanyu/learn/cpp/cppPrimer/ch12/test.txt");
}

ostream& print(ostream &out, const QueryResult &result) {
    out << "element occurs " << result.m_lines->size() << " times" << "\n";
    
    for (int index : *result.m_lines) {
        out << "\t" << "(line " << index << ") " << result.m_data->at(index-1) << "\n";
    }
    return out;
}

void runQueries(const string &filename) {

    ifstream in(filename);
    TextQuery tq(in);
    
    while (true) {
        cout << "enter word to lock for, or q to quit: ";
        string s;
        if (!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl;
    }
}
