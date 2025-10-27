// Christer Karlsson
#include <iostream>

void print_array(int *a, int len) {
    std::cout << "{" << a[0];
    for(int k=1; k<len; k++) {
        std::cout << ", " << a[k];
    }
    std::cout << "}" << std::endl;
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void heapify(int a[], int len, int i) {
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;

    if(left < len && a[left] > a[largest])
        largest = left;
    if(right < len && a[right] > a[largest])
        largest = right;
    if(largest != i) {
        swap(a[i], a[largest]);
        heapify(a, len, largest);
    }
}
// Main sort function
void heapSort(int a[], int len) {
    // Change array to a heap
    for(int i=len/2-1; i>=0; i--)
        heapify(a, len, i);
    // deleteMax
    for(int i = len-1; i>=0; i--) {
        // put current max at end
        swap(a[0], a[i]);
        // heapify once more
        heapify(a, i, 0);
    }
}

int main() {
    int a[] = { 4, 15, 2, 9, 18, 11, 6, 7};
    int len = sizeof(a)/sizeof(a[0]);

    // Function call
    std::cout << "Unsorted array: ";
    print_array(a, len);
    heapSort(a, len);
    std::cout << "Sorted array is: ";
    print_array(a, len);

    return 0;
}