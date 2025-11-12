#include "SubsetSum.h"
#include <iostream>
#include <set>

int main() {
    // Test cases from assignment
    run_case(std::multiset<int>{2, 2, 2, 2, 2, 3}, 10);
    run_case(std::multiset<int>{2, 2, 2, 2, 2, 3}, 15);
    run_case(std::multiset<int>{0, 2, 4, 5, 6, 8, 10}, 21);
    run_case(std::multiset<int>{0, 2, 4, 5, 6, 8, 10}, 32);
    run_case(std::multiset<int>{}, 0);
    run_case(std::multiset<int>{},5);
    run_case(std::multiset<int>{9},9);
    run_case(std::multiset<int>{9}, 10);
    run_case(std::multiset<int>{0,1,2}, 0);
    run_case(std::multiset<int>{0,1,2},3);
    run_case(std::multiset<int>{5,5,5,5}, 10);
    run_case(std::multiset<int>{5,5,5,5}, 11);
    run_case(std::multiset<int>{1,2,3,4,5,6,7,8,9,10}, 55);
    
    return 0;
}
