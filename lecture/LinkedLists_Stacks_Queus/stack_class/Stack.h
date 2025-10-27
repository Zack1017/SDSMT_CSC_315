//
// Created by kchri on 1/20/2025.
//
#ifndef STACK_PROJ_STACK_H
#define STACK_PROJ_STACK_H
#include <iostream>

typedef int node_type;
class Stack {
    // A class to create a node
    class node {
        node_type data {};
        node *next = nullptr;
    public:
        node() = default;
        explicit node(node_type d, node *n) : data(d), next(n) {};
        ~node() = default;

        friend class Stack;
    };

private:
    typedef node *node_ptr;
    node_ptr headptr;

public:
    // Constructor and Destructor
    Stack() = default;
    ~Stack() = default;
    // Methods
    void push(int data);
    bool isEmpty();
    int top();
    void pop();
    void display();

};

#endif //STACK_PROJ_STACK_H
