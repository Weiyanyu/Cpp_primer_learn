#include <iostream>
#include <vector>
#include "hasPtr.h"
#include <algorithm>
#include <functional>
#include <memory>

#include "debugDelete.h"


using namespace std;

template <typename It, typename V>
auto fcn(It beg, It end, V v) -> decltype(*end)
{
    while (beg != end) {
        if (*beg == v) {
            return *beg;
        }
        beg++;
    }
    return *end;
}

template <typename T, typename F >
int compare(const T &v1, const T &v2, F f) {
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}

bool myCompare(int lhs, int rhs) {
    std::cout << "use my compare" << std::endl;
    return lhs < rhs;
}

template <typename T> 
void f1(T &&t) {
    std::cout << t << std::endl;
}

void f(int v1, int &v2) {
    cout << v1 << " " << ++v2 << endl;
}

template <typename F, typename T1, typename T2>
void flip1(F f, T1 &&t1, T2 &&t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));
    cout << "flip1 : " << t1 << endl; 
}



int main() {
    int i = 0;
    int j = 1;
    f(i, j);
    cout << j << endl;
    flip1(f, j, 42);
    cout << j << endl;
}