/*
 * C++ program to create a global function as a friend
 * function of some class
 *
 * ckarlsso 11/27/2024
 */
#include <iostream>

/* the Base class */
class Foo {

private:
    int private_variable;
protected:
    int protected_variable;
public:
    Foo() {
        private_variable = 10;
        protected_variable = 99;
    }
    ~Foo() = default;

    /* friend function declaration */
    friend void friendFunction(Foo& obj);
};

/* declare and define a friend function */
void friendFunction(Foo& obj) {
    std::cout << "Private Variable: " << obj.private_variable
         << std::endl;
    std::cout << "Protected Variable: " << obj.protected_variable;
}

/* main function to test the class methods */
int main() {
    Foo obj;
    friendFunction(obj);
    return 0;
}