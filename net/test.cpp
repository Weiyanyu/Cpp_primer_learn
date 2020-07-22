#include <iostream>
#include "threadPool.h"

using namespace std;

void func1() {
    for (int i = 0; i < 10; i++) {
        std::cout << i << " " << std::flush;
    }
    std::cout << std::endl;
}

int main() {
    ThreadPool pool(2);
    
    auto f1 = pool.enqueue(func1);
    auto f2 = pool.enqueue(func1);

    f1.get();
    f2.get();
}