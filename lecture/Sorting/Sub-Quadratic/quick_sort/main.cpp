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

int partition(int a[], int start, int end) {

    int pivot = a[start];

    int count = 0;
    for(int i = start+1; i<= end; i++) {
        if(a[i] <= pivot)
            count++;
    }
    // Place pivot at the right place
    int pivotIndex = start+count;
    swap(a[pivotIndex], a[start]);
    // Sort left and right
    int i=start, j=end;
    while(i<pivotIndex && j > pivotIndex) {
        while(a[i] <= pivot)
            i++;
        while(a[j] > pivot)
            j--;
        if(i < pivotIndex && j > pivotIndex)
            swap(a[i++], a[j--]);
    }
    return pivotIndex;
}

void quickSort(int a[], int start, int end) {
    // base case
    if(start >= end)
        return;
    // Partition
    int p = partition(a, start, end);
    // Sort left side
    quickSort(a, start, p-1);
    // Sort right side
    quickSort(a, p+1, end);

}

int main() {
    int a[] = { 4, 15, 2, 9, 18, 11, 6, 7};
    int len = sizeof(a)/sizeof(a[0]);

    // Function call
    quickSort(a, 0, len-1);
    // Display array
    std::cout << "Sorted array is: ";
    print_array(a, len);

    return 0;
}
