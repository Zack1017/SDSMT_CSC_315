//
// Created by kchri on 12/16/2024.
//
#include <fstream>
#include <limits>
#include "MinHeap.h"

/* A utility function to swap two elements
 * Could also have used std::swap(T&, T&) */
void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

/* Private data fields, and methods */
/* Constructor: Creates a heap of a given size */
MinHeap::MinHeap(int cap) {
    heap_size = 0;
    capacity = cap;
    harr = new int[cap];
}
/* A recursive method to heapify a subtree with
 * the root at given index. This method assumes
 * that the subtrees are already heapified. */
void MinHeap::MinHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l] < harr[i])
        smallest = l;
    if (r < heap_size && harr[r] < harr[smallest])
        smallest = r;
    if (smallest != i) {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}
/* A helper method to traverse from left to right and
 * print the heap structure in level order to a DOT-file. */
void MinHeap::dotHelper(std::ofstream &myfile) {
    myfile << "graph {" << std::endl;
    for(int i =0; i < heap_size/2; i++) {
        myfile << "   " << harr[i];
        if (left(i) < heap_size && right(i) < heap_size) {
            myfile << " -- {" << harr[left(i)];
            myfile << ", " << harr[right(i)] << "}";
        }
        else if (left(i) < heap_size)
            myfile << " -- " << harr[left(i)];
        myfile << ";" << std::endl;
    }
}
/* A helper function to print the heap structure to a png-file */
void MinHeap::graphHelper(Agraph_t* &g) {
    // Each node is a tree so maximum three nodes
    Agnode_t *ro;
    Agnode_t *lc;
    Agnode_t *rc;
    // Traverse the array
    for(int i =0; i < heap_size/2; i++) {
        // Add the root node to the graph
        ro = agnode(g, (char *) std::to_string(harr[i]).c_str(), TRUE);
        if (left(i) < heap_size) {
            // We have a left node add it and the edge to the graph
            lc = agnode(g, (char *) std::to_string(harr[left(i)]).c_str(), TRUE);
            agedge(g, ro, lc, nullptr, TRUE);
        }
        if (right(i) < heap_size) {
            // We have a right node add it and the edge to the graph
            rc = agnode(g, (char *) std::to_string(harr[right(i)]).c_str(), TRUE);
            agedge(g, ro, rc, nullptr, TRUE);
        }
    }
}

/* Public Methods and Accessors */
/* Inserts a new key into the heap */
void MinHeap::insertKey(int k) {
    if (heap_size == capacity) {
        std::cout << "\nOverflow: Could not insertKey\n";
        return;
    }
    // First insert the new key at the end
    heap_size++;
    int i = heap_size - 1;
    harr[i] = k;
    // Fix the min heap property if it is violated
    while (i != 0 && harr[parent(i)] > harr[i]) {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}
/* Decreases value of key at index 'i' to new_val.
 * It is assumed that new_val is smaller than harr[i]. */
void MinHeap::decreaseKey(int i, int new_val) {
    harr[i] = new_val;
    while (i != 0 && harr[parent(i)] > harr[i]) {
        swap(&harr[i], &harr[parent(i)]);
        i = parent(i);
    }
}
/* Method to remove minimum element (or root) from min heap */
int MinHeap::deleteMin() {
    if (heap_size <= 0)
        return std::numeric_limits<int>::max();
    if (heap_size == 1) {
        heap_size--;
        return harr[0];
    }
    // Store the minimum value, and remove it from heap
    int root = harr[0];
    harr[0] = harr[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return root;
}
/* This function deletes key at index i. It first reduces
 * the value to minus infinity, then calls extractMin() */
void MinHeap::deleteKey(int i) {
    decreaseKey(i, std::numeric_limits<int>::min());
    deleteMin();
}
/* Writes the heap in level order to the screen */
void MinHeap::printHeap() {

    for(int i =0; i<heap_size; i++)
        std::cout << harr[i] << " ";

    std::cout << std::endl;
}
/* Save the heap structure as a DOT-file */
void MinHeap::printDot(const std::string& filename) {
    // Make sure the heap is not empty
    if(heap_size == 0)
        return;
    // Open or create a new file
    std::ofstream myfile;
    myfile.open(filename+".dot");
    std::cout << "(" << filename << ".dot created)\n";
    // Print the content of heap to the file
    dotHelper(myfile);
    // Close the file
    myfile << "}" << std::endl;
    myfile.close();
}
/* Creates a png-file of the heap structure */
bool MinHeap::graph(const std::string& filename) {
    // Make sure the heap is not empty
    if(heap_size == 0)
        return true;
    // set up a graphviz context
    GVC_t *gvc = gvContext();
    // Create a simple digraph
    Agraph_t *g = agopen((char*) &filename, Agdirected, nullptr);
    // Call the graphHelper to create all nodes in the heap
    graphHelper(g);
    // Use the directed graph layout engine
    gvLayout(gvc, g, "dot");
    // Create a DOT-file
    // gvRender(gvc, g, "dot", fopen((filename+".dot").c_str(), "w"));
    // Output the graph in .png format
    gvRender(gvc, g, "png", fopen((filename+".png").c_str(), "w"));
    // Free layout data
    gvFreeLayout(gvc, g);
    // Free graph structures
    agclose(g);
    // Make sure we freed the graph
    return(gvFreeContext(gvc));
}
