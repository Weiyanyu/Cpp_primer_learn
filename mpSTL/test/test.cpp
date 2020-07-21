#include <iostream>
#include <cassert>

#include "mpvector.h"

using namespace std;

void testMpVector();

int main() {
    testMpVector();
    return 0;
}

void testMpVector() {
    MpVector<int> nums;
    assert(nums.size() == 0);
    assert(nums.capacity() == 0);

    nums.push_back(1);
    assert(nums.size() == 1);
    assert(nums.capacity() == 1);  

    nums.push_back(2);
    assert(nums.size() == 2);
    assert(nums.capacity() == 2);

    nums.push_back(3);
    assert(nums.size() == 3);
    assert(nums.capacity() == 4);

    nums.push_back(4);
    assert(nums.size() == 4);
    assert(nums.capacity() == 4);

    nums.push_back(5);
    assert(nums.size() == 5);
    assert(nums.capacity() == 8);

    nums.push_back(6);
    assert(nums.size() == 6);
    assert(nums.capacity() == 8);
    
}