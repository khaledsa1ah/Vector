#include <iostream>
#include "Vector.cpp"
#include <algorithm>
#include <vector>

int main() {
    std::vector<int> d;
    XYVector<int> arr;
    arr.push_back(5);
    arr.push_back(2);
    arr.push_back(3);
    arr.push_back(5);
    arr.push_back(7);
    arr.push_back(8);
    arr.push_back(9);
    arr.push_back(10);

    XYVector<int>::Iterator it = arr.begin();
    XYVector<int>::Iterator it2 = arr.end();
    std::cout << arr << std::endl;


    for( XYVector<int>::Iterator it = arr.begin(); it != arr.end(); it++){
        std::cout << *it << std::endl;
    }

}
