//
// Created by kchri on 11/24/2024.
//
#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include "AVLTree.h"

// Constructor
AVLTree::AVLTree() {
    root = nullptr;
}
AVLTree::AVLTree(std::initializer_list<int> other) {
    root = nullptr;
    for(const auto& el : other)
        insert(el);
}
// Destructor
AVLTree::~AVLTree() {
    erase(root);
    root = nullptr;
}
// A utility function to get the height of the tree
int AVLTree::height(node *curr) {
    if (curr == nullptr)
        return 0;
    return curr->height;
}
// Get Balance factor of node N
int AVLTree::getBalance(node *curr) {
    if (curr == nullptr)
        return 0;
    return height(curr->left) - height(curr->right);
}
// A utility function to right rotate subtree rooted with y
node *AVLTree::rightRotate(node *y) {
    node *x = y->left;
    node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left),
                         height(y->right)) + 1;
    x->height = std::max(height(x->left),
                         height(x->right)) + 1;

    // Return new root
    return x;
}
// A utility function to left rotate subtree rooted with x
node *AVLTree::leftRotate(node *x) {
    node *y = x->right;
    node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(height(x->left),
                         height(x->right)) + 1;
    y->height = std::max(height(y->left),
                         height(y->right)) + 1;

    // Return new root
    return y;
}
// Helper function to find minimum value node in the subtree rooted at `curr`
node *AVLTree::getMinimumKey(node* curr) {
    while (curr->left != nullptr) {
        curr = curr->left;
    }
    return curr;
}
// Recursive help function to insert a key into a AVL
node *AVLTree::insertNode(node *curr, int data) {
    // Normal BST insert
    if (curr == nullptr)
        return new node(data);

    if (curr->data >= data)
        curr->left = insertNode(curr->left, data);
    else
        curr->right = insertNode(curr->right, data);
    // Update height of the ancestor node
    curr->height = 1 + std::max(height(curr->left),
                                height(curr->right));

    /* Get the balance factor of this ancestor node
       to check whether this node became unbalanced */
    int balance = getBalance(curr);
    // If it is unbalanced, there are four cases
    // Left Left Case
    if (balance > 1 && data < curr->left->data)
        return rightRotate(curr);
    // Right Right case
    if (balance < -1 && data > curr->right->data)
        return leftRotate(curr);
    // Left Right Case
    if (balance > 1 && data > curr->left->data) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    // Right Left Case
    if (balance < -1 && data < curr->right->data) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}
// Recursive help function to delete a key from an AVL
node *AVLTree::deleteNode(node *curr, int key) {
    /* Standard BST delete
       --- base case --- */
    if (curr == nullptr) {
        std::cout << "Unable to delete " << key << std::endl;
        return curr;
    }
    /* If the key to be deleted is  smaller than the
       root's key, then it lies in left subtree */
    if (key < curr->data)
        curr->left = deleteNode(curr->left, key);
    /* If the key to be deleted is greater than the
       root's key, then it lies in right subtree */
    else if (key > curr->data)
        curr->right = deleteNode(curr->right, key);
    // if key is same as root's key, then This is the node to be deleted
    else {
        std::cout << "Deleted or moved " << key << std::endl;
        // node has no child
        if (curr->left == nullptr and curr->right == nullptr) {
            return nullptr;
        }
        // node with only one child or no child
        else if (curr->left == nullptr) {
            node *temp = curr->right;
            free(curr);
            return temp;
        }
        else if (curr->right == nullptr) {
            node *temp = curr->left;
            free(curr);
            return temp;
        }

        /* node with two children: Get the inorder successor
        (smallest in the right subtree) */
        node *temp = getMinimumKey(curr->right);
        // Copy the inorder successor's content to this node
        curr->data = temp->data;
        // Delete the inorder successor
        curr->right = deleteNode(curr->right, temp->data);
    }

    /* Added part to balance the tree */
    // Update  height of the current node
    curr->height = 1 + std::max(height(curr->left),
                                height(curr->right));

    /* Get the balance factor of this  node to check
       whether this node became unbalanced */
    int balance = getBalance(curr);
    // If it is unblanced, there are four cases
    // Left Left Case
    if (balance > 1 && getBalance(curr->left) >= 0)
        return rightRotate(curr);
    // Right Right case
    if (balance < -1 && getBalance(curr->right) <= 0)
        return leftRotate(curr);
    // Left Right Case
    if (balance > 1 && getBalance(curr->left) < 0) {
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
    }
    // Right Left Case
    if (balance < -1 && getBalance(curr->right) > 0) {
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
    }
    return curr;
}

// A utility function to find the node with key value
node* AVLTree::find(node *curr, const int key) {
    if(curr == nullptr || curr->data == key)
        return curr;
    if( key < curr->data)
        return find(curr->left, key);
    else
        return find(curr->right, key);
}

// A utility function to erase all the keys in the tree
void AVLTree::erase(node *curr) {
    if(curr == nullptr)
        return;
    /* Recursively delete each subtree */
    erase(curr->left);
    erase(curr->right);
    /* Deleting the node */
    delete curr;
}

// A utility function to do inorder traversal of BST
void AVLTree::preOrder(node *curr) {
    if (curr != nullptr) {
        std::cout << curr->data <<", ";
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

// A utility function to print the tree in DOT format
void AVLTree::dotHelper(node *curr, std::ofstream &myfile) {
    std::queue<node*> Q;

    Q.push(curr);
    while( !Q.empty()) {
        if(Q.front()->left != nullptr || Q.front()->right != nullptr)
            myfile << '\t' << Q.front()->data << " -- {";
        if(Q.front()->left != nullptr) {
            Q.push(Q.front()->left);
            myfile << (Q.front()->left)->data;
        }
        if(Q.front()->right != nullptr) {
            Q.push(Q.front()->right);
            myfile << " " << (Q.front()->right)->data;
        }
        if(Q.front()->left != nullptr || Q.front()->right != nullptr)
            myfile << "}" << std::endl;
        Q.pop();
    }

}
/* Method to create a png-file with graphviz */
void AVLTree::graphHelper(Agraph_t* &g) {
    std::queue<node*> Q;
    Q.push(root);
    int tn = 0;
    // It is a tree so maximum three nodes
    Agnode_t *ro;
    Agnode_t *le;
    Agnode_t *ri;
    // Iterate through all the nodes in the tree
    while (!Q.empty()) {
        // If the root of the subtree is not empty
        if (nullptr != Q.front()) {
            // Create a graph node for the root of the subtree
            ro = agnode(g, (char *) std::to_string(Q.front()->data).c_str(), 1);
            // Is there a left child?
            if (nullptr != Q.front()->left) {
                // Create a graph node for the left child
                le = agnode(g, (char *) std::to_string(Q.front()->left->data).c_str(), 1);
                // Create an edge from root to left child
                agedge(g, ro, le, nullptr, 1);
                // Push left child on the queue
                Q.push(Q.front()->left);
            }
            // Is there a right child?
            if (nullptr != Q.front()->right) {
                // Create a graph node for the right child
                ri = agnode(g, (char *) std::to_string(Q.front()->right->data).c_str(), 1);
                // Create an edge from root to right child
                agedge(g, ro, ri, nullptr, 1);
                // Push right child on the queue
                Q.push(Q.front()->right);
            }
            // Pop the root of the subtree off the queue
            Q.pop();
        }
    }
}

/* All the public methods for the AVL Tree */
/* Method to insert a new node */
void AVLTree::insert(int data) {
    root = insertNode(root, data);
}

/* Method to remove a node */
void AVLTree::remove(int data) {
    root = deleteNode(root, data);
}

/* Method to see if a value is in the tree */
bool AVLTree::search(int data) {
    if(find(root, data) != nullptr)
        return true;
    else
        return false;
}

/* Method to empty the tree */
void AVLTree::deleteTree() {
    erase(root);
    // Create an empty root
    root = nullptr;
}

/* Method to print the tree */
void AVLTree::printTree() {
    std::cout << "{";
    preOrder(root);
    std::cout << "\b\b}" << std::endl;
}

/* Method to create a dot-file for graphviz */
void AVLTree::dotPrint(char* filename) {
    if(root == nullptr)
        return;
    // open a file for output
    std::ofstream myfile;
    myfile.open(filename);
    myfile << "graph {" << std::endl;
    // traverse and print to the file
    dotHelper(root, myfile);
    // finish output and close the file
    myfile << "}" << std::endl;
    myfile.close();
}

/* Method to print the tree as an image */
bool AVLTree::graph(const std::string& filename) {
    // Make sure the heap is not empty
    if(nullptr == root)
        return true;
    // set up a graphviz context
    GVC_t *gvc = gvContext();
    // Create a simple digraph
    Agraph_t *g = agopen((char*) &filename, Agundirected, nullptr);
    // Call the graphHelper to create all nodes in the heap
    graphHelper(g);
    // Use the directed graph layout engine
    gvLayout(gvc, g, "dot");
    // Create a DOT-file
    gvRender(gvc, g, "dot", fopen((filename+".dot").c_str(), "w"));
    // Output the graph in .png format
    gvRender(gvc, g, "png", fopen((filename+".png").c_str(), "w"));
    // Free layout data
    gvFreeLayout(gvc, g);
    // Free graph structures
    agclose(g);
    // Make sure we freed the graph
    return(gvFreeContext(gvc));
}