#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <numeric>
#include <memory>

#include "blob.h"

using namespace std;


int main() {
    StrBlob b1;
    {
        StrBlob b2 = {"a", "b", "c"};
        b1 = b2;
        b2.push_back("d");
    }

    std::cout << b1.size() << std::endl;
}