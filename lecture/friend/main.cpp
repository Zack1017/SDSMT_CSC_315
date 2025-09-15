/*
 * C++ Code to demonstrate the
 * functioning of a friend class
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

    /* friend class declaration */
    friend class friendClass;
};

/* Class anotherClass is declared as a friend inside
 * class Foo. Therefore, anotherClass is a friend of
 * Foo, and has access Foo's private members. */
class friendClass {
public:
    /* Accessor */
    void display(Foo& t) {
        std::cout << "The value of Private Variable = "
             << t.private_variable << std::endl;
        std::cout << "The value of Protected Variable = "
             << t.protected_variable;
    }
};

/* main function to test the class methods */
int main() {
    Foo obj;
    friendClass fri_obj;
    fri_obj.display(obj);

    return 0;
}