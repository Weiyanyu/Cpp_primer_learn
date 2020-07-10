#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <numeric>
#include <memory>

#include "employee.h"

using namespace std;


int main() {
    Employee e1("yeonon");
    Employee e2(e1);
    Employee e3 = e2;

    std::cout << e1.getId() << " " << e2.getId() << " " << e3.getId() << std::endl;
}