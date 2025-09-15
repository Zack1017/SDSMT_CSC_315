#include <iostream>
#include <climits>

class NaturalNumber {
private:
    unsigned int value;

public:
    // Constructor
    NaturalNumber(unsigned int val = 0) : value(val) {
        if (val > INT_MAX)              // Ensure Natural Number is {0, 1, 2, ...}
            value = 0;
    }
    // Destructor
    ~NaturalNumber() = default;

    // Successor
    NaturalNumber Successor() {
        if (this->value != INT_MAX)
            this->value += 1;
        return *this;
    }
    NaturalNumber Successor(NaturalNumber& num) {
        if (num.value != INT_MAX)
            this->value = num.value+1;
        return *this;
    }

    // Tests
    static bool isZero(const NaturalNumber& num) {
        return (num.value == 0);
    }
    static bool isEqual(const NaturalNumber& num1, const NaturalNumber& num2) {
        return (num1.value == num2.value);
    }

    // Add Natural Numbers
    NaturalNumber Add(const NaturalNumber& other) {
        if(this->value + other.value <= INT_MAX)
            this->value += other.value;
        else
            this->value = INT_MAX;
        
        return *this;
    }
    static NaturalNumber Add(const NaturalNumber& n1, const NaturalNumber& n2) {
        return NaturalNumber(n1.value + n2.value);
    }

    // Subract Natural Numbers
    NaturalNumber Subtract(const NaturalNumber& other) {
        if(this->value < other.value)
            this->value = 0;
        else
            this->value -= other.value;
        
        return *this;
    }
    static NaturalNumber Subtract(const NaturalNumber& n1, const NaturalNumber& n2) {
        return NaturalNumber(n1.value - n2.value);
    }    

    // Output operator
    friend std::ostream& operator<<(std::ostream& os, const NaturalNumber& num) {
        os << num.value;
        return os;
    }

};

int main() {
    NaturalNumber n1 = -3;
    NaturalNumber n2;
    n2.Successor(n1);

    std::cout << "Init:     " << n1 << ", "<< n2 << std::endl; 
    std::cout << "test1:    " << (NaturalNumber::isZero(n1) ? "true" : "false") << std::endl;
    std::cout << "test2:    " << (NaturalNumber::isEqual(n1, n2) ? "true" : "false") << std::endl;
    std::cout << "Add:      " << n1 << " + " << n2 << " = " << NaturalNumber::Add(n1, n2) << std::endl;
    std::cout << "Subtract: " << n1<< " - " << n2 << " = " << NaturalNumber::Subtract(n1, n2) << std::endl;

    return 0;
}