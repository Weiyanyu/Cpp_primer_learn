#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <numeric>


using namespace std;

void elimDups(vector<string> &words);

int main() {
    istream_iterator<int> in(cin), eof;
    cout << accumulate(in, eof, 0) << endl;
}

void elimDups(vector<string> &words) {
    sort(words.begin(), words.end());
    auto uniqueEnd = unique(words.begin(), words.end());
    words.erase(uniqueEnd, words.end());
}