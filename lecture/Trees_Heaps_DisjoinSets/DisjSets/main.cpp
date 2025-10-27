
// Driver Code
#include "DisjSet.h"

int main() {

    DisjSet set(8);
    set.unionSets(4,5);
    set.unionSets(6,7);
    set.unionSets(4,6);
    set.unionSets(3,4);
    set.display();
    set.graph("graph");

    DisjSet set2(16);
    set2.unionSets(0,1);
    set2.unionSets(2,3);
    set2.unionSets(4,5);
    set2.unionSets(6,7);
    set2.unionSets(0,2);
    set2.unionSets(4,6);
    set2.unionSets(0,4);
    set2.unionSets(8,9);
    set2.unionSets(10,11);
    set2.unionSets(12,13);
    set2.unionSets(14,15);
    set2.unionSets(8,10);
    set2.unionSets(12,14);
    set2.unionSets(8,12);
    set2.unionSets(0,8);
    set2.display();
    set2.find(14);
    set2.display();
    set2.graph("graph2");

    return 0;
}
