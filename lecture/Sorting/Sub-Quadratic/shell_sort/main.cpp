#include <iostream>

void print_array(int *a, int len) {
    std::cout << "{" << a[0];
    for(int k=1; k<len; k++) {
        std::cout << ", " << a[k];
    }
    std::cout << "}" << std::endl;
}
// Main sort function
void shellSort(int a[], int len) {
    int gap, key, i, j, k;

    for(gap = len/2; gap>0; gap /= 2) {
        for(i = gap; i<len; ++i) {
            key = a[i];
            for(j=i; j>=gap && key < a[j-gap]; j -= gap)
                a[j] = a[j - gap];
            a[j] = key;
        }
        std::cout << gap <<"-sort: ";
        std::cout << "{" << a[0];
        for(k=1; k<len; k++) {
            std::cout << ", " << a[k];
        }
        std::cout << "}" << std::endl;
    }
}

int main() {
    int a[] = {81,94,11,96,12,35,17,95,28,58,41,75,15};
    int len = sizeof(a)/sizeof(a[0]);

    shellSort(a, len);
    std::cout << "Sorted: ";
    print_array(a, len);

    return 0;
}

