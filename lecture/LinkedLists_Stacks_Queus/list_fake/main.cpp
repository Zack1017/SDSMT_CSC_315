#include <iostream>

void insert(int list[][2], int &headptr, int num, int &size) {
    int curr, prev;

    list[size][0] = num;
    curr = headptr;
    // insert at beginning
    if(curr == -999 || num <= list[curr][0]) {
        list[size][1] = headptr;
        headptr = size;
        size++;
        return;
    }
    // insert in middle or end
    prev = headptr;
    while(curr != -999 && list[curr][0] < num) {
        prev = curr;
        curr = list[curr][1];
    }
    // adjust links
    list[prev][1] = size;
    list[size][1] = curr;
    size++;
}

int find(int list[][2], int headptr, int num) {
    int tmp;
    tmp = headptr;
    // look for the number
    while(tmp !=-999 && list[tmp][0] != num)
        tmp = list[tmp][1];
    // if 'NULL' number was not in list
    if(tmp == -999)
        std::cout << "Number is not in the list" << std::endl;

    return(tmp);
}

int delete_num(int list[][2], int &headptr, int num, int &size) {
    int location = find(list, headptr, num);
    int prev = headptr;
    int prev_last = headptr;

    // Try to delete a number not in list
    if(location == -999)
        return (location);

    // Do we delete the headptr?
    if(headptr == location){
        // If last element in the array, only change headptr
        if(headptr == size-1)
            headptr = list[location][1];
            // last element will move to headptr spot
        else {
            // Find previous to the last element
            while(list[prev_last][1] != size-1)
                prev_last = list[prev_last][1];
            // Update the pointers
            headptr = list[location][1];
            list[prev_last][1] = location;
            list[location][0] = list[size-1][0];
            list[location][1] = list[size-1][1];
        }
    }
    // Is it the last element in array? If so it is easy to remove
    else if(location == size-1) {
        // find what element points to the last
        while(list[prev][1] != location)
            prev = list[prev][1];
        // update the pointers
        list[prev][1] = list[location][1];
    }
    // Ok neither of the easy ones
    else {
        // Find previous to the deleted element
        while(list[prev][1] != location)
            prev = list[prev][1];
        // Is the last element the headptr?
        if(headptr == size-1)
            headptr = location;
        else {
            // Find previous to the last element
            while (list[prev_last][1] != size - 1)
                prev_last = list[prev_last][1];
            // Update the pointers
            list[prev_last][1] = list[prev][1];
        }
        list[prev][1] = list[location][1];
        list[location][0] = list[size-1][0];
        list[location][1] = list[size-1][1];
    }
    // Update the size of the list
    size--;
    return(location);
}

void print(int list[][2], int headptr) {
    int tmp;
    tmp = headptr;
    std::cout << "list: ";
    while(tmp !=-999) { // -999 = NULL
        std::cout << list[tmp][0] << " ";
        tmp = list[tmp][1]; // tmp = tmp->next
    }
    std::cout << std::endl;
}

int main() {
    int list[10][2] ={{18,3},{6,4},{14,0},{31,-999},{9,2}}; //Note the list is right now capped at 10 elements
    int headptr = 1;
    int size = 5;       // This and the lines above is where we ended in class.
    print(list, headptr);

    int num[] = {3, 7, 50};

    // Try to delete a number that is not in list
    if (delete_num(list, headptr, 42, size) != -999)
        print(list, headptr);
    // Insert a number smaller than all the others
    insert(list, headptr, num[0], size);
    print(list, headptr);
    // Delete a head-pointer that is also last
    if (delete_num(list, headptr, 3, size) != -999)
        print(list, headptr);
    // Delete the last element in array
    if (delete_num(list, headptr, 9, size) != -999)
        print(list, headptr);
    // Insert two more numbers
    insert(list, headptr, num[1], size);
    insert(list, headptr, num[2], size);
    print(list, headptr);
    // Delete a head-pointer that is not last
    if (delete_num(list, headptr, 6, size) != -999)
        print(list, headptr);
    // Delete a number neither head-pointer nor last
    if (delete_num(list, headptr, 18, size) != -999)
        print(list, headptr);

    return 0;
}