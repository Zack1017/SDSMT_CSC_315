// Christer Karlsson
#include <iostream>
void print_array(int *a, int len) {
    std::cout << "{" << a[0];
    for(int k=1; k<len; k++) {
        std::cout << ", " << a[k];
    }
    std::cout << "}" << std::endl;
}

// Inplace swap
void swap(int & a, int & b) {
    a += b;
    b = a-b;
    a -= b;
}

int main() {
    int a[] = {15, 2, 9, 18, 11, 6};
    int len = sizeof(a)/sizeof(a[0]);
    int i, j;
    for(i=1; i<len; i++) {
        for(j=0; j<len-i; j++) {
            if(a[j] > a[j+1])
                swap(a[j], a[j+1]);
        }
        print_array(a, len);
    }
    return 0;
}

