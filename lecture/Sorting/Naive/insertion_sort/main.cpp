// Christer Karlsson
#include <iostream>

void print_array(int *a, int len){
    std::cout << "{" << a[0];
    for(int k=1; k<len; k++) {
        std::cout << ", " << a[k];
    }
    std::cout << "}" << std::endl;
}

int main() {
    int a[] = {15, 2, 9, 18, 11, 6};
    int len = sizeof(a)/sizeof(a[0]);
    int key, i, j, k;

    for(i=1; i < len; i++) {
        key = a[i];
        for(j=i; j>0 && key < a[j-1]; j--) {
            std::cout << i << ", " << j << ": ";
            std::cout << a[j] << ", " << a[j-1] << " -> ";
            a[j] = a[j-1];
            std::cout << a[j] << ", " << a[j-1] << std::endl;
        }
        a[j] = key;
        print_array(a, len);
    }

    return 0;
}