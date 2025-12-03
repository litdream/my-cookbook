#include "llist.hpp"
#include <iostream>

int main() {
    LList list;
    list.push(10);
    list.push(20);
    list.push(5);

    std::cout << "List: ";
    list.print();

    std::cout << "List size: " << list.size() << std::endl;
    std::cout << "Min value: " << list.min() << std::endl;
    std::cout << "Max value: " << list.max() << std::endl;

    std::cout << "Searching for 10: " << (list.search(10) ? "Found" : "Not found") << std::endl;
    std::cout << "Searching for 15: " << (list.search(15) ? "Found" : "Not found") << std::endl;

    std::cout << "Popping value: " << list.pop() << std::endl;
    std::cout << "List after pop: ";
    list.print();

    list.remove(10);
    std::cout << "List after removing 10: ";
    list.print();

    return 0;
}
