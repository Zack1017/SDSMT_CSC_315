#include "rbtree.h"

//Node
RBTree::Node::Node(int k, Color c) : key(k), color(c), left(nullptr), right(nullptr), parent(nullptr)
{

}



RBTree::RBTree()
{
    NIL = new Node(0, BLACK);
    NIL->left =NIL->right = NIL->parent = NIL; 
    root = NIL; 
    node_count =0; 
}



RBTree::~RBTree()
{
    clear();
    delete NIL;
}



void RBTree::insert(int key)
{
    Node* x = new Node(key, RED);
    x->left = x->right = x->parent = NIL; 
    bstInsert(x);
    insertFixup(x);
    ++node_count;
}



bool RBTree::erase(int key)
{
    Node* x = searchNode(key);
    
    if(x == NIL)
    {
        return false; 
    }
    eraseNode(x);
    node_count = node_count - 1; 
    return true; 
}



bool RBTree::contains(int key)
{
    return searchNodeConst(key) !=NIL; 
}



void RBTree::clear()
{
    clearSubTree(root);
    root = NIL; 
    node_count =0; 
}



std::size_t RBTree::size()
{
    return node_count; 
}



bool RBTree::to_dot(const std::string& path)
{
    std::ofstream out(path);
    if (!out)
    {
        return false; 
    }
    out << "digraph RBTree {\n";
    out << "  node [shape=circle style=filled fontname=\"Helvetica\"];\n";
    out << "  edge [fontname=\"Helvetica\"];\n";
    
    if(root == NIL)
    {
        out << "  empty [label=\"∅\" shape=box style=rounded, color=black, fillcolor=white];\n";
        out << "}\n";
        return true;
    }

    std::queue<const Node*> q; 
    q.push(root);
    int nil_id_gen = 0; 
    while(!q.empty())
    {
        auto x = q.front();
        q.pop();
        if (x == NIL) continue;
        std::string fill = (x->color==RED ? "red" : "black");
        std::string font = "white";
        out << "  n" << x << " [label=\"" << x->key << "\" fillcolor=\"" << fill << "\" fontcolor=\"" << font << "\"];\n";

        if (x->left != NIL) {
            out << "  n" << x << " -> n" << x->left << " [label=\"L\"];\n";
            q.push(x->left);
        } else {
            out << "  nil" << nil_id_gen << " [shape=box, width=0.2, height=0.2, label=\"\", style=filled, fillcolor=\"black\"];\n";
            out << "  n" << x << " -> nil" << nil_id_gen << " [label=\"L\"];\n";
            ++nil_id_gen;
        }
        if (x->right != NIL) {
            out << "  n" << x << " -> n" << x->right << " [label=\"R\"];\n";
            q.push(x->right);
        } else {
            out << "  nil" << nil_id_gen << " [shape=box, width=0.2, height=0.2, label=\"\", style=filled, fillcolor=\"black\"];\n";
            out << "  n" << x << " -> nil" << nil_id_gen << " [label=\"R\"];\n";
            ++nil_id_gen;
        }
    }
    out << "}\n";
    return true;
}



bool RBTree::validate_rb_properties(bool verbose)
{
    if(root == NIL)
    {
        return true; 
    }
    if(root->color != BLACK)
    {
        if(verbose)std::cerr << "Root is not black\n";
        return false;
    }
    if(!validate_local(root, verbose))
    {
        return false; 
    }
    int expected = -1; 
    return validate_black_height(root, 0, expected, verbose); 
}



void RBTree::clearSubTree(Node* x)
{
    if(x == NIL)
    {
        return; 
    }
    clearSubTree(x->left);
    clearSubTree(x->right);
    delete x; 
}



RBTree::Node* RBTree::searchNode(int key) 
{
    Node* x = root;

    while (x != NIL) 
    {
        if (key == x->key) 
        {
            return x;
        }
        x = (key < x->key) ? x->left : x->right;
    }
    return NIL;
}



const RBTree::Node* RBTree::searchNodeConst(int key) const 
{
    const Node* x = root;

    while (x != NIL) 
    {
        if (key == x->key)
        {
            return x;
        } 
        x = (key < x->key) ? x->left : x->right;
    }
    return NIL;
}



void RBTree::leftRotate(Node* x)
{
    Node* y= x-> right;
    x->right = y->left; 

    if(y->left != NIL)
    {
        y->left->parent =x;
    }
    y->parent = x->parent;
    if(x->parent == NIL) root =y; 
    else if(x == x->parent->right)
    {
        x->parent->right =y;
    }
    else
    {
        x->parent->left =y;
    } 
    y-> right =x;
    x-> parent =y;
}



void RBTree::rightRotate(Node* x) 
{
    Node* y = x->left;
    x->left = y->right;

    if (y->right != NIL)
    {
        y->right->parent = x;
    } 
    y->parent = x->parent;

    if (x->parent == NIL)
    {
        root = y;
    } 
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    } 
    else 
    {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}



void RBTree::bstInsert(Node* z) 
{
    Node* y = NIL;
    Node* x = root;

    while (x != NIL) 
    {
        y = x;
        if (z->key < x->key)
        {
            x = x->left;
        } 
        else 
        {
            x = x->right;
        }
    }
    z->parent = y;

    if (y == NIL)
    {
        root = z;
    } 
    else if (z->key < y->key)
    {
        y->left = z;
    } 
    else
    {
        y->right = z;
    } 

    z->left = z->right = NIL;
    z->color = RED;
}



void RBTree::insertFixup(Node* z) 
{
    while (z->parent->color == RED) 
    {
        if (z->parent == z->parent->parent->left) 
        {
            Node* y = z->parent->parent->right;

            if (y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } 
            else 
            {
                if (z == z->parent->right) 
                {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } 
        else 
        {
            Node* y = z->parent->parent->left;

            if (y->color == RED) 
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else 
            {
                if (z == z->parent->left) 
                {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }

    root->color = BLACK;
    root->parent = NIL;
}



void RBTree::transplant(Node* u, Node* v) 
{
    if (u->parent == NIL)
    {
        root = v;
    } 
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    } 
    else 
    {
        u->parent->right = v;
    }

    v->parent = u->parent;
}



RBTree::Node* RBTree::minimum(Node* x) const 
{
    while (x->left != NIL)
    {
        x = x->left;
    } 
    return x;
}



void RBTree::eraseNode(Node* z) 
{
    Node* y = z;
    Color y_original_color = y->color;
    Node* x;

    if (z->left == NIL) 
    {
        x = z->right;
        transplant(z, z->right);
    } 
    else if (z->right == NIL) 
    {
        x = z->left;
        transplant(z, z->left);
    } 
    else 
    {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        if (y->parent == z) 
        {
            x->parent = y;
        } 
        else 
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (y_original_color == BLACK)
    {
        deleteFixup(x);
    } 
}



void RBTree::deleteFixup(Node* x) 
{
    while (x != root && x->color == BLACK) 
    {
        if (x == x->parent->left) 
        {
            Node* w = x->parent->right;

            if (w->color == RED) 
            {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) 
            {
                w->color = RED;
                x = x->parent;
            } 
            else 
            {
                if (w->right->color == BLACK) 
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } 
        else 
        {
            Node* w = x->parent->left;
            if (w->color == RED) 
            {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) 
            {
                w->color = RED;
                x = x->parent;
            } 
            else 
            {
                if (w->left->color == BLACK) 
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}



bool RBTree::validate_local(const Node* x, bool verbose) const 
{
    if (x == NIL)
    {
        return true;
    } 
    if (x->color == RED) 
    {
        if (x->left->color == RED || x->right->color == RED) 
        {
            if (verbose)
            {
                std::cerr << "Red violation at key " << x->key << "\n";
            } 
            return false;
        }
    }
    return validate_local(x->left, verbose) && validate_local(x->right, verbose);
}



bool RBTree::validate_black_height(const Node* x, int blacks, int& expected, bool verbose) const 
{
    if (x->color == BLACK)
    {
        blacks++;
    } 
    if (x == NIL) 
    {
        if (expected == -1)
        {
            expected = blacks;
        } 
        if (expected != blacks) 
        {
            if (verbose)
            {
                std::cerr << "Black-height mismatch; expected " << expected << " got " << blacks << "\n";
            } 
            return false;
        }
        return true;
    }
    return validate_black_height(x->left, blacks, expected, verbose) && validate_black_height(x->right, blacks, expected, verbose);
}