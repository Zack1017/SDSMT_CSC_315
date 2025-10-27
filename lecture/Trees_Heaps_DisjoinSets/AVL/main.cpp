#include <iostream>
#include "AVLTree.h"

/* Driver function to test the methods */
int main() {

    AVLTree t = {50, 60, 40, 45, 30};
    t.printTree();

    t.insert(20);
    t.graph((char*) "file1");
    t.deleteTree();

    for(int key: {50, 40, 60, 30, 45, 55, 65, 70})
        t.insert(key);
    t.printTree();

    t.insert(75);
    t.graph((char*) "file2");
    if(t.search(35))
        std::cout << "35 is in the tree \n";
    else
        std::cout << "35 is not in the tree \n";
    t.deleteTree();

    for(int key: {50, 40, 60, 30, 45, 55, 65, 62, 70})
        t.insert(key);
    t.printTree();

    t.insert(75);
    t.graph((char*) "file3");
    t.deleteTree();

    for(int key: {50, 40, 60, 30, 45, 55, 65, 70})
        t.insert(key);
    t.printTree();

    t.insert(75);
    t.graph((char*) "file4");
    t.deleteTree();

    for(int key: {50, 40, 60, 55, 67})
        t.insert(key);
    t.printTree();

    t.insert(75);
    t.graph((char*) "file5");
    t.deleteTree();

    for(int key: {50, 40, 60, 30, 45})
        t.insert(key);
    t.printTree();

    t.insert(75);
    t.graph((char*) "file6");
    t.deleteTree();

    for(int key: {50, 40, 60, 30, 45, 55, 65, 70})
        t.insert(key);
    t.printTree();

    t.remove(45);
    t.graph((char*) "file7");
    t.printTree();
    t.remove(30);
    t.graph((char*) "file8");
    t.deleteTree();
    
    return 0;
}
