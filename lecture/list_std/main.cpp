#include <iostream>
#include <list>

void print(std::list<int> &list){
    std::list<int>::iterator spot;

    std::cout <<"List:";
    for(spot = list.begin(); spot != list.end(); spot++)
        std::cout << " " << *spot;
    std::cout << std::endl;
}

void find_num(std::list<int> &mylist, int num){
    auto curr = mylist.begin();

    std::cout << num;
    while((curr != mylist.end()) && (*curr != num))
        curr++;
    if(curr == mylist.end())
        std::cout << " not in list" << std::endl;
    else
        std::cout << " is in list" << std::endl;
}

void delete_num(std::list<int> &mylist, int num){
    ulong size1, size2;

    std:: cout << "Deleting " << num << std::endl;
    size1 = mylist.size();
    mylist.remove(num);
    size2 = mylist.size();
    if(size1 == size2)
        std::cout << "Number was not in list" << std::endl;
    else
        print(mylist);
}

int main() {
    std::list<int>  mylist;
    int             add_num[]={3,2,1,5};

    // Add a number
    for(int i=0; i < sizeof(add_num)/sizeof(*add_num); i++)
        mylist.push_back(add_num[i]);

    print(mylist);

    // Find a number
    find_num(mylist, 4);
    find_num(mylist, 3);

    // Delete a number
    delete_num(mylist, 4);
    delete_num(mylist, 3);

    // Delete entire list
    std::cout << "Deleting entire list\n";
    mylist.clear();
    print(mylist);

    // Add numbers
    add_num[1] = 1;
    std::list<int> new_list (add_num, add_num+4);
    print(new_list);
    new_list.unique();
    print(new_list);

    return 0;
}