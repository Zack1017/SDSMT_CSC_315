//
// Created by kchri on 11/24/2024.
//
#ifndef BST_CLASS_BST_H
#define BST_CLASS_BST_H

/* BST Tree class */
class BST {
    /* Node class with all attributes for a
     * node and contractor and destructor */
    class node {
        int data{};
        node *left = nullptr;
        node *right = nullptr;
    /* Public methods */
    public:
        node() = default;
        explicit node(int d) : data(d) {};
        ~node() = default;

        friend class BST;
    };
    /* create a root node */
    node *root;
/* Private methods */
    node* insertNode(node *curr, int data);
    node* erase(node* curr);
    void inorderTree(node *curr);
    node* find(node* curr, int key);
    static node* findMaximumKey(node *curr);
    node* deleteNode(node* &nd, int key);
/* public methods */
public:
    // Constructor and Destructor
    BST();
    ~BST();
    // Public methods
    void insert(int d);
    void remove(int key);
    bool search(int x);
    void clear();
    void printTree();
    bool graph(const std::string& filename);
};

#endif //BST_CLASS_BST_H
