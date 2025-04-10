// test_list.cpp
// Prof Allen
// FGCU Computing and Software Engineering
// Test harness for a List ADT to test insert and other functionality
// of a list implementation
// ------------------------------------------------------------
#include <iostream>
#include <cstdlib> // random numbers
#include <ctime>   // seed random numbers
#include "List.h"

void printList(fgcu::List<int> &list);

int main() {

    fgcu::List<int> intList;

    std::srand(std::time(NULL));

    std::cout << "\nNumber of elements to insert: ";
    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        int number = std::rand() % (n * 10);
        int position = std::rand() % (n + 1) - 1;

        std::cout << "insert " << number << " @ " << position << std::endl;
        printList(intList);

        intList.insert(number, position);
    }

    printList(intList);

    return 0;
}


void printList(fgcu::List<int> &list) {
    std::cout << "List {";

    int size = list.getSize();
    for (int i=0; i < size; ++i) {
        std::cout << list.read(i);

        if (i < size - 1)
            std::cout << ",";
    }
    std::cout << "}" << std::endl;
}