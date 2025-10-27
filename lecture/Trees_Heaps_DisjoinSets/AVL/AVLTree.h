//
// Created by kchri on 11/24/2024.
//
#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H
#include <initializer_list>
#include <graphviz/gvc.h>
#include <graphviz/cgraph.h>

/* Node class with all attributes for a node
 * and contractor and destructor */
class node {
    int data{};
    node *left = nullptr;
    node *right = nullptr;
    int height=1;
/* Public methods */
public:
    node() = default;
    explicit node(int d) : data(d) {};
    ~node() = default;
    // Make AVL a friend class
    friend class AVLTree;
};

/* AVL Tree class */
class AVLTree {
    node *root;
/* Private methods */
    static int height(node *curr);
    static int getBalance(node *curr);
    static node *rightRotate(node *y);
    static node *leftRotate(node *x);
    static node *getMinimumKey(node *curr);
    node *insertNode(node *curr, int data);
    node *deleteNode(node *curr, int key);
    node* find(node *curr, int key);
    void erase(node *curr);
    void preOrder(node *curr);
    void dotHelper(node *root, std::ofstream& filename);
    void graphHelper(Agraph_t* &g);
/* Public methods */
public:
    // Constructor and Destructor
    AVLTree();
    AVLTree(std::initializer_list<int> other);
    ~AVLTree();
    // Public methods
    void insert(int data);
    void remove(int data);
    bool search(int data);
    void deleteTree();
    void printTree();
    void dotPrint(char* filename);
    bool graph(const std::string& filename);
};

#endif //AVL_AVLTREE_H
