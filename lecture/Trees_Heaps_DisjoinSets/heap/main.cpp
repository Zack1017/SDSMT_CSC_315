/*
 * C++ program to demonstrate common Heap Operations
 *
 * Problem statement:
 * Implement at least:
 *   - create a new heap,
 *   - delete the heap,
 *   - keep track of parent and children
 *   - At least one, preferably three display methods;
 *     - Level order traversal
 *     - Create a DOT-file for use with Graphviz
 *     - Create a png.file
 * Have at least the following public methods:
 *   - insert a key into the heap
 *   - get the value of the minimum key
 *   - delete the minimum key
 *   - decrease the value of a given key
 *   - delete a key at a given index
 *   - access to the private display methods.
 */
#include "MinHeap.h"

// Driver program to test above functions
int main() {
    MinHeap h(15);  // Life is easier if the capacity is 2^k-1
    /* Create the heap in the slides */
    for(auto el : {13, 65, 16, 24, 31, 19, 68, 21, 26, 32})
        h.insertKey(el);
    // Display the heap
    h.printHeap();
    h.printDot("file1");
    h.graph("file1");

    // Insert 14
    h.insertKey(14);
    // Display the new heap
    h.printHeap();
    h.printDot("file2");
    h.graph("file2");

    // Delete the minimum key (13)
    h.deleteMin();
    // Display the new heap
    h.printHeap();
    h.printDot("file3");
    h.graph("file3");

    // Delete the value at index 5 (19)
    h.deleteKey(5);
    // Display the new heap
    h.printHeap();
    h.printDot("file4");
    h.graph("file4");

    return 0;
}
