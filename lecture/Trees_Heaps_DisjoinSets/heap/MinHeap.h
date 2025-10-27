//
// Created by kchri on 12/16/2024.
//
#ifndef HEAP_MINHEAP_H
#define HEAP_MINHEAP_H

#include <iostream>             // Need this here for std::string
#include <graphviz/gvc.h>       // Could be in the cpp-file,
                                // but prefer to have gvc and cgraph together.
#include <graphviz/cgraph.h>    // Need this for Agraph_t

/* A class for Min Heap */
class MinHeap {
    /* Private Members */
    int *harr;      // pointer to array of elements in heap
    int capacity;   // maximum possible size of min heap
    int heap_size;  // Current number of elements in min heap

    /* Private methods */
    // Get the index of the parent
    static int parent(int i) { return (i-1)/2; }
    // to get index of left child of node at index i
    static int left(int i) { return (2*i + 1); }
    // to get index of right child of node at index i
    static int right(int i) { return (2*i + 2); }
    // to heapify a subtree with the root at given index
    void MinHeapify(int i);
    // Helper method th create a DOT-file
    void dotHelper(std::ofstream &myfile);
    // helper method to print the heap
    void graphHelper(Agraph_t* &g);

    /* Public Accessors and Mutators */
public:
    // Constructor & Destructor
    explicit MinHeap(int capacity);
    ~MinHeap() = default;   // A default destructor works fine

    // Inserts a new key 'k'
    void insertKey(int k);
    // to extract the root which is the minimum element
    int deleteMin();
    // Decreases key value of key at index i to new_val
    void decreaseKey(int i, int new_val);
    // Returns the minimum key (key at root) from min heap
    int getMin() { return harr[0]; }
    // Deletes a key stored at index i
    void deleteKey(int i);
    // Methods to display the heap in various form
    void printHeap();
    void printDot(const std::string& filename);
    bool graph(const std::string& filename);
};

#endif //HEAP_MINHEAP_H
