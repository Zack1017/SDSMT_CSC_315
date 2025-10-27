//
// Written by kchri on 8/15/2022.
//
#include <iostream>

typedef int node_type;
struct node_rec {
    node_type num;
    node_rec *next;
};
typedef node_rec *node_ptr;

// Insert
void insert(node_ptr temp, node_ptr &headptr) {
    node_ptr curr;
    node_ptr prev;

    if(headptr == nullptr) {
        headptr = temp;
        return;
    }
    if(temp-> num < headptr-> num) {
        temp -> next = headptr;
        headptr = temp;
        return;
    }

    prev = headptr;
    curr = headptr;

    while((curr != nullptr) && (curr->num < temp->num)) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = temp;
    temp->next = curr;
}

// Delete
void delete_node(node_type temp_num, node_ptr &headptr) {
    node_ptr curr;
    node_ptr prev;

    prev = headptr;
    curr = headptr;

    while((curr != nullptr) && (curr->num != temp_num)) {
        prev = curr;
        curr = curr->next;
    }
    if(curr == nullptr){
        std::cout << "Number not in list" << std::endl;
        return;
    }
    if(curr == headptr)
        headptr = curr->next;
    else
        prev->next = curr->next;
    delete(curr);
}

// Find Node
void find_node(node_type find_num, node_ptr headptr, node_ptr &location) {
    node_ptr curr;

    curr = headptr;

    while((curr != nullptr) && (curr->num != find_num)) {
        curr = curr->next;
    }

    location = curr;

    if(location == nullptr) {
        std::cout << "Number not in list" << std::endl;
        return;
    }
}

void delete_list(node_ptr &headptr) {
    node_ptr tmp;

    tmp = headptr;
    while(tmp != nullptr) {
        tmp = tmp->next;
        delete(headptr);
        headptr = tmp;
    }
    std::cout << std::endl;
}

void print_list(node_ptr headptr) {
    node_ptr tmp;

    std::cout << "   LIST of NUMBERS   " << std::endl;
    tmp = headptr;
    while(tmp != nullptr) {
        std::cout << "   " << tmp->num;
        tmp = tmp->next;
    }
    std::cout << std::endl;
    std::cout << std::endl;
}
int main() {
    node_ptr  headptr;
    node_type num_to_delete;
    node_type num_to_find;
    node_ptr  location;
    node_ptr  tmp;

    headptr = nullptr;

    tmp = new(node_rec);
    tmp->num = 3;
    std::cout << "Add " << tmp->num << " to list." << std::endl;
    tmp->next = nullptr;
    insert(tmp, headptr);
    print_list(headptr);

    tmp = new(node_rec);
    tmp->num = 2;
    std::cout << "Add " << tmp->num << " to list." << std::endl;
    tmp->next = nullptr;
    insert(tmp, headptr);

    tmp = new(node_rec);
    tmp->num = 1;
    std::cout << "Add " << tmp->num << " to list." << std::endl;
    tmp->next = nullptr;
    insert(tmp, headptr);

    tmp = new(node_rec);
    tmp->num = 5;
    std::cout << "Add " << tmp->num << " to list." << std::endl;
    tmp->next = nullptr;
    insert(tmp, headptr);
    print_list(headptr);

    std::cout << "Searching for 4" << std::endl;
    find_node(4, headptr, location);
    if(location != nullptr)
        std::cout << "Item " << location->num << " found." << std::endl;
    std::cout << "Searching for 2" << std::endl;
    find_node(2, headptr, location);
    if(location != nullptr)
        std::cout << "Item " << location->num << " found." << std::endl;

    std::cout << "Deleting 3" << std::endl;
    delete_node(3, headptr);
    print_list(headptr);

    std::cout << "Deleting entire list" << std::endl;
    delete_list(headptr);
    print_list(headptr);

    return 0;
}