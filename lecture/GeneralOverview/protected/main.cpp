/*
 * C++ program to demonstrate
 * protected access modifier
 *
 * ckarlsso 11/27/2024
 */
#include <iostream>

/* Base class */
class Parent {
    /* protected data members */
protected:
    int id_protected;
};

/* Subclass or derived class from public base class */
class Child : public Parent {
public:
    void setId(int id) {
        /* Child class is able to access the inherited
         * protected data members of base class */
        id_protected = id;
    }
    void displayId() {
        std::cout << "id_protected is: " << id_protected << std::endl;
    }
};

/* main function */
int main() {
    /* Creating instance(object) of class */
    Child obj1;
    /* Member function of the derived class can access
     * the protected data members of the base class */
    obj1.setId(81);
    obj1.displayId();
    return 0;
}
