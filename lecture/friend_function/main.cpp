/*
 * C++ program to create a member function of
 * another class as a friend function
 *
 * ckarlsso 11/27/2024
 */
#include <iostream>

/* forward definition is required */
class Foo;

/* another class in which function is declared */
class anotherClass {
public:
    void memberFunction(Foo& obj);
};

/* the Base class for which friend is declared */
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
    friend void anotherClass::memberFunction(Foo&);
};

/* friend function definition */
void anotherClass::memberFunction(Foo& obj) {
    std::cout << "Private Variable: " << obj.private_variable
         << std::endl;
    std::cout << "Protected Variable: " << obj.protected_variable;
}

/* main function to test the class methods */
int main() {
    Foo obj;
    anotherClass fri_obj;
    fri_obj.memberFunction(obj);

    return 0;
}