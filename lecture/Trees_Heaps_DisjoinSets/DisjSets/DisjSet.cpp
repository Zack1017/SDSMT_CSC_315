//
// Created by kchri on 1/19/2025.
//
#include "DisjSet.h"
/** Private methods
 * Method to create a png-file with graphviz */
void DisjSet::graphHelper(Agraph_t* &g) {
    // It is a disjoint set, so only interested in parent and child.
    Agnode_t *pa;
    Agnode_t *ch;
    // Iterate through all the nodes in the set
    for (int i = 0; i <s.size(); ++i) {
        ch = agnode(g, (char *) std::to_string(i).c_str(), 1);
        if(s[i] >= 0 ) {
            pa = agnode(g, (char *) std::to_string(s[i]).c_str(), 1);
            agedge(g, pa, ch, nullptr, 1);
        }
    }
}

// Constructor
DisjSet::DisjSet(int numElements) : s(numElements, -1) {

}

/**
 * Perform a find. (a recursive call)
 * Error checks omitted again for simplicity.
 * Return the set containing x.
 */
int DisjSet::find(int x) const {
    if(s[x] < 0)
        return x;
    else
        return find(s[x]);
}

/**
 * Perform a find with path compression.
 * Return the set containing x.
 */
int DisjSet::find(int x) {
    if( s[x] < 0 )
        return x;
    else
        return s[x] = find(s[x]);
}

/**
 * Union two disjoint sets by size.
 * For simplicity, we assume root1 and root2 are distinct
 * and represent set names.
 * root1 is the root of set 1.
 * root2 is the root of set 2.
 */
void DisjSet::unionSets(int root1, int root2) {
    if (s[root2] < s[root1]) { // root2 is larger
        s[root2] += s[root1];
        s[root1] = root2;      // Make root2 new root
    }
    else {
        s[root1] += s[root2];
        s[root2] = root1;      // Make root1 new root
    }
}
// Method to print the tree as an image //
bool DisjSet::graph(const std::string& filename) {
    // set up a graphviz context
    GVC_t *gvc = gvContext();
    // Create a simple digraph
    Agraph_t *g = agopen((char*)"g", Agundirected, nullptr);
    // Call the helper function
    graphHelper(g);
    // Use the directed graph layout engine
    gvLayout(gvc, g, "dot");
    // Output the graph in .png format
    gvRender(gvc, g, "png", fopen((filename+".png").c_str(), "w"));
    // Free layout data
    gvFreeLayout(gvc, g);
    // Free graph structures
    return(agclose(g));
}
// Method to display graph in level order
void DisjSet::display() {
    std::cout << "| ";
    for(auto i: s)
        std::cout << i << " | ";
    std::cout << std::endl;
}