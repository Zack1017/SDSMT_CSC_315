//
// Written by kchri on 8/15/2022.
//
#include <iostream>
#include "linklist.h"

int main() {
    LinkList  mylist{};
    node_type del_num;
    node_type find_num;
    node_type add_num;
    int       error_code;

    // Insert test
    int test[4] = {3,2,5,1};
    for (int i : test) {
        add_num = i;
        std::cout << "Add " << add_num << " to list." << std::endl;
        error_code = mylist.insert(add_num);
        if (error_code < 0)
            std::cout << "Insert failed" << std::endl;
        mylist.print();
    }
    // Find test
    find_num = 4;
    std::cout << "Searching for "<< find_num << std::endl;
    error_code = mylist.find_num(find_num);
    if (error_code < 0)
        std::cout << find_num << " not found." << std::endl;
    else
        std::cout << find_num << " is in the list." << std::endl;
    find_num = 2;
    std::cout << "Searching for "<< find_num << std::endl;
    error_code = mylist.find_num(find_num);
    if (error_code < 0)
        std::cout << find_num << " not found." << std::endl;
    else
        std::cout << find_num << " is in the list." << std::endl;
    // Delete an element
    del_num = 3;
    error_code = mylist.delete_num(del_num);
    if (error_code < 0)
        std::cout << "Item not in the list" << std::endl;
    else
        std::cout << "Item removed from list" << std::endl;
    mylist.print();
    // Erase entire list
    std::cout << "Deleting entire list" << std::endl;
    mylist.erase();
    mylist.print();

    return 0;
}