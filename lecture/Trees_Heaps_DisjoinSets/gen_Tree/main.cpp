/*
 * C++ program to demonstrate a generalized tree
 *
 * Problem statement:
 * A node can have an arbitrary number of children.
 * Instead of have a list of child pointers, we
 * create a node with two pointers. The first one
 * points to the first child (LeftChild), and the
 * second to the first sibling (RightSibling).
 * This creates a tree with a level structure.
 * Implement at least:
 *   - create a new LC-RS-Tree,
 *   - delete the tree,
 *   - keep track of parents, children and siblings.
 *   - At least one, preferably three display methods;
 *     - Level order traversal,
 *     - Create a DOT-file for use with Graphviz,
 *     - Create a png.file.
 * Have at least the following public methods:
 *   - insert a key to a parent node
 *     ( the method will need to know what node will be the parent,
 *       then find if the key should be inserted as child or sibling),
 *   - find if a key is present in the tree,
 *   - clear the entire tree
 *   - access to the private display methods.
 */
#include <iostream>
#include "LC_RS_Tree.h"

int main() {
    LC_RS_Tree t1;

    t1.insert('A');
    // Create the tree in the slides
    t1.insert('A', 'B');
    t1.insert('A', 'C');
    t1.insert('A', 'D');
    t1.insert('A', 'E');
    t1.insert('D', 'H');
    t1.insert('A', 'F');
    t1.insert('A', 'G');
    t1.insert('E', 'I');
    t1.insert('E', 'J');
    t1.insert('J', 'P');
    t1.insert('J', 'Q');
    t1.insert('F', 'K');
    t1.insert('F', 'L');
    t1.insert('F', 'M');
    t1.insert('G', 'N');


    // Expected output is:
    // A B C D E F G H I J K L M N P Q
    t1.printLevelOrder();
    // Test the find method
    if(t1.find('F'))
        std::cout << "F is in the tree" << std::endl;
    else
        std::cout << "F is NOT in the tree" << std::endl;
    if(t1.find('Z'))
        std::cout << "Z is in the tree" << std::endl;
    else
        std::cout << "Z is NOT in the tree" << std::endl;
    // Files saved in cmake-build-debug
    t1.printDot("tree1");
    // a png-file of the tree
    t1.graph("tree1");

    return 0;
}