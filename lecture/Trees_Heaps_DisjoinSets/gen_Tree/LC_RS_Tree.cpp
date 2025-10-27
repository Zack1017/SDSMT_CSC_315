//
// Created by kchri on 2/01/2025.
//
#include <queue>            // Needed for traversal
#include <utility>          // Allows me to use std::pair<T, T>
#include "LC_RS_Tree.h"

// Adds a child node to n
Node *LC_RS_Tree::addChild(Node * n, char data) {
    if( nullptr == n)
        return nullptr;
    // Check if child list is not empty.
    if (n->leftChild)
        return addSibling(n->leftChild, data);
    else
        return (n->leftChild = new Node(data));
}
// Adds a sibling to the end of 'list' with starting with n
Node *LC_RS_Tree::addSibling(Node *n, char data) {
    if (nullptr == n)
        return nullptr;
    // Find the end of the sibling 'list'
    while(n->rightSibling)
        n = n->rightSibling;
    // Update the last sibling
    return (n->rightSibling = new Node(data));
}
// Traverses the tree in depth first order to find a node
Node *LC_RS_Tree::findNode(Node *n, char key) {
    // If the tree is empty or the
    // value in the node is the key
    if(!n || n->data == key)
        return n;
    // Need a queue
    std::queue<Node*> q;
    Node* curr = n->leftChild;
    q.push(curr);
    // Search the tree level by level
    while(!q.empty()) {
        // Place front of queue in current
        curr = q.front();
        q.pop();
        while(curr) {
            // Do we have the node?
            if(curr->data == key)
                return curr;
            if(curr->leftChild)
                q.push(curr->leftChild);
            curr = curr->rightSibling;
        }
    }
    // We end here if the key is not in the tree
    return nullptr;
}
// Traverses tree in depth first order
void LC_RS_Tree::traverseTree(Node *root) {
    // empty tree?
    if (!root)
        return;
    std::cout << root->data << " ";
    // single node?
    if (!root->leftChild)
        return;
    // Create a queue and enqueue root's child
    std::queue<Node*> q;
    Node* curr = root->leftChild;
    q.push(curr);
    // While there are things still in the queue
    while (!q.empty()) {
        // Grab first item from the queue
        curr = q.front();
        q.pop();
        // Print next level of taken out item and enqueue
        // next level's children
        while (curr) {
            std::cout << curr->data << " ";
            // If we have a child push onto the queue
            if (curr->leftChild) {
                q.push(curr->leftChild);
            }
            curr = curr->rightSibling;
        }
    }
    std::cout << std::endl;
}
// A helper method to traverse and print
// the heap structure to a DOT-file
void LC_RS_Tree::dotHelper(std::ofstream &myfile) {
    // Create a queue and a current Node
    std::queue<std::pair<Node*, Node*>> Q;
    Node* curr;
    // A pair is the root node of the subtree and its first child.
    std::pair<Node*, Node*> pair(root, root->leftChild);
    Q.push(pair);
    // While there are still elements in the pairs queue
    while(!Q.empty()) {
        // Add an edge between the node and its child,
        // this is the first pair in the pair-queue.
        myfile << "\t" << Q.front().first->data << " -- " << Q.front().second->data << std::endl;
        // All the siblings should be on the same rank
        myfile << "\t" << "{ rank = same" << std::endl;
        // Print next level of the item grabbed from the queue
        // Set current to the first child of the first item
        curr = Q.front().second;
        Q.pop();
        while (curr) {
            // If we have a child, push the node and its child on the pair-queue
            if (curr->leftChild) {
                pair.first = curr;
                pair.second = curr->leftChild;
                Q.push(pair);
            }
            // If it has a sibling print the node and sibling
            if(curr->rightSibling)
                myfile << "\t\t" << curr->data << " -- " << curr->rightSibling->data << std::endl;
            // Next node is the sibling to the right at same level
            curr = curr->rightSibling;
        }
        // Close of the same rank
        myfile << "\t" << "}" << std::endl;
    }
}

// Public Methods and Accessors
// Method to insert a new node into an empty tree
void LC_RS_Tree::insert(char value) {
    // Base case tree is empty
    Node *newNode = new Node(value);
    if (root == nullptr) {
        root = newNode;
        return;
    }
}
// Method to insert a new node as child to node 'key'
void LC_RS_Tree::insert(char key, char value) {
    Node *n = findNode(root, key);
    addChild(n, value);
}
// Method to answer if a key is in the structure
bool LC_RS_Tree::find(char key) {
    if(findNode(root, key))
        return true;
    return false;
}
// Function to print the tree in level order (Breadth-First Search)
void LC_RS_Tree::printLevelOrder() {
    traverseTree(root);
}
// Function for creating a DOT-file
void LC_RS_Tree::printDot(const std::string& filename) {
    if(!root)
        return;
    // Open or create a new file
    std::ofstream myfile;
    myfile.open(filename+".dot");
    std::cout << "(" << filename << ".dot created)\n";
    myfile << "graph {" << std::endl;
    // Print the content of heap to the file
    dotHelper(myfile);
    // Close the file
    myfile << "}" << std::endl;
    myfile.close();
}
//
bool LC_RS_Tree::graph(const std::string& filename) {
    if(!root)
        return true;
    // set up a graphviz context
    GVC_t *gvc = gvContext();
    // Create a simple digraph
    Agraph_t *g = agopen((char*) (filename).c_str(), Agdirected, nullptr);
    Agsym_t  *attr = agattr(g,0, (char*) "rank", (char*) "");

    // Each node is a tree so maximum three nodes
    Agnode_t *ro;
    Agnode_t *lc;
    Agnode_t *rs;

    // Create a queue and a current Node paired with child
    std::queue<std::pair<Node*, Node*>> Q;
    Node* curr;
    // A pair consisting of the root of the subtree and its child
    std::pair<Node*, Node*> pair(root, root->leftChild);
    Q.push(pair);

    // Traverse through the entire structure
    while(!Q.empty()) {
        // We are going to need sub-graphs
        Agraph_t *hs;
        // Put the data in the graph nodes.
        ro = agnode(g, &Q.front().first->data, TRUE);
        lc = agnode(g, &Q.front().second->data, TRUE);
        agedge(g, ro, lc, nullptr, TRUE);
        // Create a subgraph rooted at this node
        hs = agsubg(g, (char *) &Q.front().first->data, FALSE);
        if(!hs) {
            hs = agsubg(g, &Q.front().first->data, TRUE);
            agset(hs, (char *) "rank", (char *) "same");
            // std::cout << agnameof(agraphof(hs)) << ": ";
        }
        // The second in the pair is the first child
        curr = Q.front().second;
        Q.pop();
        while(curr) {
            lc = agnode(hs, &curr->data, TRUE);
            // std::cout << agnameof(lc) << ' ';
            if (curr->leftChild) {
                pair.first = curr;
                pair.second = curr->leftChild;
                Q.push(pair);
            }
            if (curr->rightSibling) {
                rs = agnode(hs, &curr->rightSibling->data, TRUE);
                agedge(hs, lc, rs, nullptr, TRUE);
            }
            curr = curr->rightSibling;
        }
        //std::cout << std::endl;
    }

    // Use the directed graph layout engine
    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "dot", fopen((filename+".dot").c_str(), "w"));
    // Output the graph in .png format
    gvRender(gvc, g, "png", fopen((filename+".png").c_str(), "w"));
    // Free layout data
    gvFreeLayout(gvc, g);
    // Free graph structures
    agclose(g);

    return(gvFreeContext(gvc));
}

