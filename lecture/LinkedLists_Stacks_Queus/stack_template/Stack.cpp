//
// Created by kchri on 1/20/2025.
//
#include "Stack.h"

// Push new element onto stack
template<class node_type>
void Stack<node_type>::push(node_type data) {
    node<node_type> *tmp = new node(data, headptr);
    // Check if stack is full
    if(!tmp) {
        std::cout << "STACK OVERFLOW" << std::endl;
        exit(1);
    }
    // Make tmp new top.
    headptr = tmp;
}
// Check if stack is empty
template<class node_type>
bool Stack<node_type>::isEmpty() {
    if(nullptr == headptr)
        return(true);
    else
        return(false);
}
// Peek at the top
template <class node_type>
node_type Stack<node_type>::top() {
    if(!isEmpty())
        return(headptr->el);
    else {
        std::cout << "STACK EMPTY" << std::endl;
        exit(1);
    }
}
// Remove top element from stack
template <class node_type>
void Stack<node_type>::pop() {
    node<node_type> *tmp;
    // Check if empty
    if(isEmpty()) {
        std::cout << "STACK UNDERFLOW" << std::endl;
        exit(1);
    }
    else {
        tmp = headptr;
        headptr = headptr->next;
        free(tmp);
    }
}
// Normally not a functionality of stack, but good for decoding
template <class node_type>
void Stack<node_type>::display() {
    node<node_type> *tmp;

    if(isEmpty()) {
        std::cout << "STACK UNDERFLOW" << std::endl;
        exit(1);
    }
    else {
        tmp = headptr;
        while(nullptr != tmp) {
            std::cout << tmp->el << "->";
            tmp = tmp->next;
        }
        std::cout << "NULL" << std::endl;
    }
}

template class Stack<int>;
