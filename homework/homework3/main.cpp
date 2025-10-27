#include "ExpressionTree.h"
#include <iostream>
#include <string>

int main() {
    std::vector<std::string> tests = {
            "a+b",
            "a*(b+c)",
            "(a+b)*c",
            "a+b*c-d",
            "(x+y)*(z+w)",
            "(a+b*c)+((d*e+f)*g)"  // target expression (output last)
        };

        for (size_t i = 0; i < tests.size(); ++i) {
            std::cout << "\n==============================\n";
            std::cout << "Expression " << (i + 1) << ": " << tests[i] << "\n";
            ExpressionTree tree(tests[i]);
            tree.printResults();

            std::string dotFile = "expressionTree_" + std::to_string(i + 1) + ".dot";
            tree.writeDot(dotFile);
#ifdef HAVE_GRAPHVIZ
            std::string pngFile = "expressionTree_" + std::to_string(i + 1) + ".png";
            tree.renderPNG(pngFile);
#else
            std::cout << "Run:\n  dot -Tpng " << dotFile
                      << " -o expressionTree_" << (i + 1) << ".png\n";
#endif
        }

        std::cout << "\nAll expressions processed successfully.\n";
        std::cout << "The last expression was: (a+b*c)+((d*e+f)*g)\n";

    } 
