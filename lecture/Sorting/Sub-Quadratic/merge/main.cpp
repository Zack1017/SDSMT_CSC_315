// Christer Karlsson
#include <iostream>

using namespace std;

void merge(int *array, int *temp, int first, int mid, int last) {
    int h = first, i = first, j = mid+1, k;

    while((h <= mid) && (j <= last)) {
        if(array[h] <= array[j])
            temp[i++] = array[h++];
        else
            temp[i++] = array[j++];
    }
    if(h > mid) {
        for(k=j; k<= last; k++)
            temp[i++] = array[k];
    }
    else {
        for(k=h; k<= mid; k++)
            temp[i++] = array[k];
    }
    for(k=first; k<=last; k++)
        array[k] = temp[k];
}

void mergesort(int *array, int *temp, int first, int last) {
    int mid;

    if(first < last) {
        mid = (first + last) /2;
        mergesort(array, temp, first, mid);
        mergesort(array, temp, mid+1, last);
        merge(array, temp, first, mid, last);
    }
}

int main() {
    int array[] = {0,3,2,5,7,6,9,4,1,8};
    int len = sizeof(array)/sizeof(array[0]);
    int temp[len];

    mergesort(array, temp, 0, len-1);

    for(int i=0; i<len; i++)
        cout << array[i] << " ";
    cout << endl;

    return 0;
}
