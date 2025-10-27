#include "ExpressionTree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cctype>

//Construction

ExpressionTree::ExpressionTree(const std::string& infix) 
{
    auto toks = tokenize(infix);
    auto postfix = infixToPostfix(toks);
    root = buildTree(postfix);
}

ExpressionTree::~ExpressionTree() 
{ 
    freeTree(root); 
}

//token

std::vector<ExpressionTree::Token> ExpressionTree::tokenize(const std::string& s) const 
{
    std::vector<Token> out;
    auto isIdentStart = [](char c)
    { 
        return std::isalpha((unsigned char)c) || c == '_'; 
    };

    auto isIdentChar  = [](char c)
    { 
        return std::isalnum((unsigned char)c) || c == '_'; 
    };

    for (size_t i=0;i<s.size();) 
    {
        char c=s[i];
        if (std::isspace((unsigned char)c)) 
        { 
            ++i; continue; 
        }
        if (isIdentStart(c)) 
        {
            size_t j=i+1; while(j<s.size() && isIdentChar(s[j])) ++j;
            out.push_back({TokType::Operand, s.substr(i,j-i)}); i=j;
        } 
        else if (std::isdigit((unsigned char)c)) 
        {
            size_t j=i+1; 
            while(j<s.size() && std::isdigit((unsigned char)s[j]))
            {
                ++j;
            }
            out.push_back({TokType::Operand, s.substr(i,j-i)});
            i=j;
        } 
        else if (c=='(') 
        { 
            out.push_back({TokType::LParen,"("});
            ++i; 
        }
        else if (c==')') 
        { 
            out.push_back({TokType::RParen,")"});
            ++i; 
        }
        else if (c=='+'||c=='-'||c=='*'||c=='/'||c=='%') 
        {
            out.push_back({TokType::Operator,std::string(1,c)});
            ++i;
        } 
        else throw std::runtime_error(std::string("Invalid char: ")+c);
    }
    return out;
}

//Postfix

std::vector<ExpressionTree::Token> ExpressionTree::infixToPostfix(const std::vector<Token>& infix) const 
{
    std::unordered_map<std::string, std::pair<int,bool>> prec = 
    {
        {"+",{1,false}},
        {"-",{1,false}},
        {"*",{2,false}},
        {"/",{2,false}},
        {"%",{2,false}}
    };
    std::vector<Token> output;
    std::stack<Token> ops;

    for (auto &t : infix) 
    {
        if (t.type==TokType::Operand) 
        {
            output.push_back(t);
        }
        else if (t.type==TokType::Operator) 
        {
            auto [p,right]=prec[t.text];
            while(!ops.empty() && ops.top().type==TokType::Operator) 
            {
                auto [p2, _] = prec[ops.top().text];
                if ((right && p<p2)||(!right && p<=p2)) 
                {
                    output.push_back(ops.top());
                    ops.pop();
                } 
                else break;
            }
            ops.push(t);
        } 
        else if (t.type==TokType::LParen)
        {
            ops.push(t);
        } 
        else if (t.type==TokType::RParen) 
        {
            while(!ops.empty() && ops.top().type!=TokType::LParen) 
            {
                output.push_back(ops.top()); ops.pop();
            }
            if (ops.empty())
            {
                throw std::runtime_error("Mismatched parentheses");
            } 
            ops.pop();
        }
    }

    while(!ops.empty()) 
    {
        if(ops.top().type==TokType::LParen)
        {
            throw std::runtime_error("Mismatched parentheses");
        } 
        output.push_back(ops.top());
        ops.pop();
    }
    return output;
}

//Tree

ExpressionTree::Node* ExpressionTree::buildTree(const std::vector<Token>& postfix) const 
{
    std::stack<Node*> st;
    for (auto &t : postfix) 
    {
        if (t.type==TokType::Operand) 
        {
            st.push(new Node(t.text));
        }
        else if (t.type==TokType::Operator) 
        {
            if (st.size()<2) 
            {
                throw std::runtime_error("Invalid postfix");
            }
            Node* r=st.top(); 
            st.pop();
            Node* l=st.top(); 
            st.pop();
            Node* n=new Node(t.text);
            n->left=l; 
            n->right=r;
            st.push(n);
        }
    }
    if (st.size()!=1)
    {
        throw std::runtime_error("Invalid postfix result");
    } 
    return st.top();
}

//Stuff

void ExpressionTree::preorder(const Node* n, std::vector<std::string>& out) const 
{
    if(!n)
    {
        return;
    }  
    out.push_back(n->val);
    preorder(n->left,out); 
    preorder(n->right,out);
}

void ExpressionTree::postorder(const Node* n, std::vector<std::string>& out) const 
{
    if(!n)
    {
        return;
    } 
    postorder(n->left,out); 
    postorder(n->right,out); 
    out.push_back(n->val);
}

bool ExpressionTree::allSingle(const Node* n) const 
{
    if(!n) 
    {
        return true;
    }
    if(n->val.size()!=1)
    {
        return false;
    } 
    return allSingle(n->left)&&allSingle(n->right);
}

std::string ExpressionTree::join(const std::vector<std::string>& v, bool compact) 
{
    std::ostringstream oss;
    for(size_t i=0;i<v.size();++i)
    {
        if(i && !compact)
        {
            oss << ' ';
        } 
        oss<<v[i];
    }
    return oss.str();
}

//DOT

void ExpressionTree::enumerate(const Node* n, std::vector<const Node*>& nodes) const 
{
    if(!n)
    {
        return; 
    } 
    nodes.push_back(n);
    enumerate(n->left,nodes); 
    enumerate(n->right,nodes);
}

void ExpressionTree::writeDot(const std::string& path) const 
{
    std::vector<const Node*> nodes; enumerate(root,nodes);
    std::unordered_map<const Node*,int> id;
    for(size_t i=0;i<nodes.size();++i)
    {
        id[nodes[i]]=i;
    } 

    std::ofstream f(path);
    f<<"strict graph g {\n";
    for(auto* n:nodes)
    {
        f<<"    "<<id[n]<<" [label=\""<<n->val<<"\"];\n";
    }
        
    for(auto* n:nodes)
    {
        if(n->left)  f<<"    "<<id[n]<<" -- "<<id[n->left]<<";\n";
        if(n->right) f<<"    "<<id[n]<<" -- "<<id[n->right]<<";\n";
    }
    f<<"}\n";
}

void ExpressionTree::freeTree(Node* n)
{
    if(!n)
    {
        return;
    } 
    freeTree(n->left);
    freeTree(n->right); 
    delete n;
}

//Print

void ExpressionTree::printResults() const 
{
    std::vector<std::string> pre, post;
    preorder(root, pre); 
    postorder(root, post);
    bool compact = allSingle(root);

    std::cout << "\nPostfix: " << join(post, compact)
              << "\nPrefix : " << join(pre, compact) << "\n";
}

//Graph

void ExpressionTree::renderPNG(const std::string& path) const 
{
    std::vector<const Node*> nodes; 
    enumerate(root,nodes);
    std::unordered_map<const Node*,Agnode_t*> agn;

    GVC_t* gvc = gvContext();
    Agraph_t* G = agopen((char*)"g", Agundirected, nullptr);
    for(size_t i=0;i<nodes.size();++i)
    {
        Agnode_t* an = agnode(G,(char*)std::to_string(i).c_str(),1);
        agset(an,(char*)"label",(char*)nodes[i]->val.c_str());
        agn[nodes[i]] = an;
    }
    for(auto* n:nodes)
    {
        if(n->left)
        {
             agedge(G,agn[n],agn[n->left],nullptr,1);
        } 
        if(n->right)
        {
            agedge(G,agn[n],agn[n->right],nullptr,1);
        } 
    }
    gvLayout(gvc,G,"dot");
    gvRenderFilename(gvc,G,"png",path.c_str());
    gvFreeLayout(gvc,G);
    agclose(G);
    gvFreeContext(gvc);
}