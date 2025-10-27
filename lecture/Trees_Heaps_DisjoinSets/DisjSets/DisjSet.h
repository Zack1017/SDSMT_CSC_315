//
// Created by kchri on 1/19/2025.
//
#ifndef DISJSETS_DISJSET_H
#define DISJSETS_DISJSET_H

#include <iostream>
#include <vector>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

class DisjSet {

private:
    std::vector<int> s;
    void graphHelper(Agraph_t* &g);

public:
    explicit DisjSet(int numElements);
    ~DisjSet() = default;
    int find(int x) const;
    int find(int x);
    void unionSets(int Root1, int Root2);
    bool graph(const std::string& filename);
    void display();
};

#endif //DISJSETS_DISJSET_H
