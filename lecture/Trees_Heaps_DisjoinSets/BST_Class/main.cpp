/*
 * C++ program to show the functions of a Binary Search tree
 *
 * Problem statement:
 * Implement at least:
 *   - create a new tree,
 *   - delete the tree
 *   - clear the tree
 *   - graph the tree using gvc and cgraph
 * Have at least the following public methods:
 *   - insert
 *   - remove
 *   - search
 * Given the root node of a binary search tree and a key value,
 * implement a function to search for the node containing that
 * key value within the tree, returning the node if found, or
 * indicating that the key does not exist in the tree.
 */
#include <iostream>
#include "BST.h"

int main() {
    int keys[] = {15, 11, 22, 4, 13, 18, 31, 1,
                  5, 14, 17, 20, 25, 19, 28};
    BST *t = new BST;

    for(int key: keys)
        t->insert(key);

    t->printTree();
    t->graph("init");
    if(t->search(5))
        std::cout << "Number is in the tree" << std::endl;
    else
        std::cout << "Number is not in the tree" << std::endl;

    t->remove(7);
    t->printTree();

    t->remove(5);
    t->printTree();

    t->remove(31);
    t->printTree();

    t->remove(22);
    t->printTree();
    t->graph("final");

    t->clear();

    delete t;

    return 0;
}
