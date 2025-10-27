#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>
#include <memory>
#include <graphviz/cgraph.h>
#include <graphviz/gvc.h>

class ExpressionTree {
public:
    explicit ExpressionTree(const std::string& infix);
    ~ExpressionTree();

    void printResults() const;
    void writeDot(const std::string& path) const;

    void renderPNG(const std::string& path) const;

private:
    struct Node {
        std::string val;
        Node* left = nullptr;
        Node* right = nullptr;
        explicit Node(std::string v) : val(std::move(v)) {}
    };

    enum class TokType { Operand, Operator, LParen, RParen };
    struct Token { TokType type; std::string text; };

    Node* root = nullptr;

    // Core logic
    std::vector<Token> tokenize(const std::string& s) const;
    std::vector<Token> infixToPostfix(const std::vector<Token>& infix) const;
    Node* buildTree(const std::vector<Token>& postfix) const;

    // Utility
    void preorder(const Node* n, std::vector<std::string>& out) const;
    void postorder(const Node* n, std::vector<std::string>& out) const;
    void enumerate(const Node* n, std::vector<const Node*>& nodes) const;
    bool allSingle(const Node* n) const;
    static std::string join(const std::vector<std::string>& v, bool compact);
    void freeTree(Node* n);
};
