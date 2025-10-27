#include "rbtree.h"
#include <iostream>
#include <vector>

int main() {
    RBTree t;

    // Build with some values
    std::vector<int> vals = {41, 38, 31, 12, 19, 8, 55, 60, 5, 35, 50};
    for (int v : vals)
    {
        t.insert(v);
    } 

    std::cout << "Size after inserts: " << t.size() << "\n";
    std::cout << "Contains 35? " << (t.contains(35) ? "yes" : "no") << "\n";
    std::cout << "Contains 99? " << (t.contains(99) ? "yes" : "no") << "\n";

    if (!t.validate_rb_properties(true)) 
    {
        std::cerr << "RB properties FAILED\n";
        return 2;
    } else 
    {
        std::cout << "RB properties OK\n";
    }

    // Export DOT
    if (t.to_dot("tree.dot"))
    {
        std::cout << "Wrote tree.dot\n";
    } 

    // erases
    t.erase(12);
    t.erase(38);
    t.erase(41);
    std::cout << "Size after erases: " << t.size() << "\n";
    if (t.to_dot("tree_after_erase.dot"))
    {
        std::cout << "Wrote tree_after_erase.dot\n";
    } 

    // Clear
    t.clear();
    std::cout << "Size after clear: " << t.size() << "\n";
    t.to_dot("tree_empty.dot");

    return 0;
}
