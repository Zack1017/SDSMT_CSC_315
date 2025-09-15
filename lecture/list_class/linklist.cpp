//
// Created by ckarlsso on 8/15/2022.
//
#include <iostream>
#include "linklist.h"

// Fill constructor
LinkList::LinkList(int n, node_type key) {
    headptr = nullptr;

    for(int i=0; i<n; i++)
        insert(key);
}
// Copy constructor
LinkList::LinkList(LinkList const&original_list) {
    headptr = nullptr;
    node_ptr temp = original_list.headptr;

    while (nullptr != temp) {
        insert(temp->num);
        temp = temp->next;
    }
}
// Destructor
LinkList::~LinkList() {
    erase();
}
// Erase
void LinkList::erase() {
    node_ptr temp;

    temp = headptr;

    while (nullptr != temp) {
        temp = temp-> next;
        delete(headptr);
        headptr = temp;
    }
}
// Insert
int LinkList::insert(node_type add_num) {
    node_ptr curr;
    node_ptr prev;
    node_ptr temp;

    temp = new(node);
    if (nullptr == temp)
        return(-1);

    temp->num = add_num;
    temp->next = nullptr;

    if(headptr == nullptr) {
        headptr = temp;
        return(1);
    }
    else if(temp->num <= headptr->num) {
        temp->next = headptr;
        headptr = temp;
        return(1);
    }

    prev = headptr;
    curr = headptr;

    while((nullptr != curr) && (curr->num <= temp->num)) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = temp;
    temp->next = curr;

    return(1);
}
// Delete
int LinkList::delete_num(node_type del_num) {
    node_ptr curr;
    node_ptr prev;

    prev = headptr;
    curr = headptr;

    while((nullptr != curr) && (curr->num != del_num)) {
        prev = curr;
        curr = curr->next;
    }
    if(nullptr == curr) {
        std::cout << "Number not in list" << std::endl;
        return(-1);
    }
    if(curr == headptr)
        headptr = curr->next;
    else
        prev->next = curr->next;
    delete(curr);

    return(1);
}
// Find Node
int LinkList::find_num(node_type find_num) {
    node_ptr curr;
    node_ptr location;

    curr = headptr;
    while((nullptr != curr) && (curr->num != find_num))
        curr = curr->next;

    location = curr;

    if(location == nullptr)
        return(-1);
    else
        return(1);
}
// Display the list
void LinkList::print() {
    node_ptr temp;

    std::cout << "   LIST of NUMBERS   " << std::endl;
    temp = headptr;
    while(nullptr != temp) {
        std::cout << "   " << temp->num;
        temp = temp->next;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}