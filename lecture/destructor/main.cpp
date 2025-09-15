/*
 * C++ program to explain constructors
 * and destructors
 *
 * ckarlsso 11/27/2024
 */
#include <iostream>

class foo {

public:
    int id {};
    // Definition for Constructor
    foo() = default;
    explicit foo(int i) : id(i) {};
    // Definition for Destructor
    ~foo() {
        std::cout << "Destructor called for id: " << id << std::endl;
    }
};

int main()   {
    foo obj1{};
    obj1.id = 9;
    foo *obj2 = new foo(7);
    for( auto i = 0; i < 5; i++ ) {
        foo obj3(i);
    }                   // Scope for obj3 ends here
    delete obj2;        // Scope for obj2 ends here
    return 0;
  }                     // Scope for obj1 ends here
