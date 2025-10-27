//
// Created by kchri on 1/20/2025.
//
#ifndef STACK_PROJ_STACK_H
#define STACK_PROJ_STACK_H
#include <iostream>

// A class to create a node
template<typename node_type>
class node {
    node_type el{};
    node *next = nullptr;
public:
    node() = default;
    explicit node(node_type d, node *n) : el(d), next(n) {}
    ~node() = default;

    template<class> friend class Stack;
};

// A class to implement a stack
template<class node_type>
class Stack {

    node<node_type> *headptr = nullptr;
public:
    // Constructor and Destructor
    Stack() = default;
    ~Stack() = default;
    // Methods
    void push(node_type el);
    bool isEmpty();
    node_type top();
    void pop();
    void display();
};

#endif //STACK_PROJ_STACK_H
