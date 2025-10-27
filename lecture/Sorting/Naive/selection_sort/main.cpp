// Christer Karlsson
#include <iostream>
void print_array(int *a, int len) {
    std::cout << "{" << a[0];
    for(int k=1; k<len; k++) {
        std::cout << ", " << a[k];
    }
    std::cout << "}" << std::endl;
}

/* An inplace swap, uses no extra
 * registers, but is slower on
 * most modern CPU architectures */
void swap(int & a, int & b) {
    a ^= b;
    b ^= a;
    a ^= b;
}

int main() {
    int a[] = {15, 2, 9, 18, 11, 6};
    int len = sizeof(a)/sizeof(a[0]);
    int i, j, tmp;
    for(i=0; i<len-1; i++) {
        for(j=i+1; j<len; j++) {
            if(a[i] > a[j])
                swap(a[i], a[j]);
        }
        print_array(a, len);
    }
    return 0;
}
