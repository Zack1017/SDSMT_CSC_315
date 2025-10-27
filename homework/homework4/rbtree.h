#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>

class RBTree
{
    public:
        enum Color : bool { BLACK=false, RED=true };

        struct Node 
        {
            int key; 
            Color color; 
            Node* left; 
            Node* right; 
            Node* parent; 
            Node(int i=0, Color c=BLACK);
        };

        RBTree();
        ~RBTree();
        RBTree(const RBTree&) = delete; 
        RBTree& operator=(const RBTree&) = delete; 

        void insert(int key);
        bool erase(int key);
        bool contains(int key);
        void clear(); 
        std::size_t size(); 
        bool to_dot(const std::string& path); 
        bool validate_rb_properties(bool verbose=false);

    private: 
        Node *root; 
        Node* NIL; 
        std::size_t node_count; 

        void clearSubTree(Node* x);
        Node* searchNode(int key);
        const Node* searchNodeConst(int key) const;
        void leftRotate(Node* x);
        void rightRotate(Node* x);
        void bstInsert(Node* x);
        void insertFixup(Node* x);
        void transplant(Node* x, Node* y);
        Node*minimum(Node* x) const;
        void eraseNode(Node* x);
        void deleteFixup(Node* x);
        bool validate_local(const Node* x, bool verbose) const; 
        bool validate_black_height(const Node* x, int blacks, int& expeted, bool verbose) const; 


};