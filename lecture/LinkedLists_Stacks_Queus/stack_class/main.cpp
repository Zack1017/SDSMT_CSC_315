#include <iostream>
#include "Stack.h"

int main() {
    Stack S;

    int A[] = {11,22,33,44};

    for(auto n : A)
        S.push(n);
    S.display();

    std::cout << "Top element is: " << S.top() << std::endl;

    S.pop();
    S.pop();
    S.display();

    std::cout << "Top element is: " << S.top() <<std:: endl;

    return 0;
}
