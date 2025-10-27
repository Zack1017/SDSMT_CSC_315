//
// Created by kchri on 1/20/2025.
//
#include "Stack.h"

// Push new element onto stack
void Stack::push(int data) {
    node_ptr tmp = new node(data, headptr);
    // Check if stack is full
    if(!tmp) {
        std::cout << "STACK OVERFLOW" << std::endl;
        exit(1);
    }
    // Make tmp new top.
    headptr = tmp;
}
// Check if stack is empty
bool Stack::isEmpty() {
    if(headptr == nullptr)
        return(true);
    else
        return(false);
}
// Peek at the top
int Stack::top() {
    if(!isEmpty())
        return(headptr->data);
    else {
        std::cout << "STACK EMPTY" << std::endl;
        exit(1);
    }
}
// Remove top element from stack
void Stack::pop() {
    node_ptr tmp;
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
void Stack::display() {
    node_ptr tmp;

    if(isEmpty()) {
        std::cout << "STACK UNDERFLOW" << std::endl;
        exit(1);
    }
    else {
        tmp = headptr;
        while(tmp != nullptr) {
            std::cout << tmp->data << "->";
            tmp = tmp->next;
        }
        std::cout << "NULL" << std::endl;
    }
}
