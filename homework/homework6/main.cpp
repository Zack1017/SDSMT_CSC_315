/*
 * C++ program to solve the 3SUM problem
 *
 * Problem statement:
 * Given a list of n real numbers does it contain
 * three elements that sum to zero.
 */
#include <iostream>
#include <set>
#include <vector>
#include <unordered_set>
#include <string>

// Type alias for clarity
using Triplet    = std::multiset<int>;
using TripletSet = std::set<Triplet>;

/* Return a multiset of a three number list
 * that are present in num and adds to 0. 
 * On^2
 */
std::set<std::multiset<int>>find3Numbers(std::vector<int>& num, int sum = 0) 
{
    std::set<std::multiset<int>> three_sum;
    int n = (int) num.size();

    /* Fix the first element as num[i] */
    for (int i = 0; i < n - 2; ++i) 
    {
        // candidates for the second value
        std::unordered_set<int> seen;  

        /* Fix the second element as num[j] */
        for (int j = i + 1; j < n; ++j) {
            int needed = sum - num[i] - num[j];

            if (seen.find(needed) != seen.end()) {
                Triplet t = { num[i], num[j], needed };
                three_sum.insert(t);
            }
            seen.insert(num[j]);
        }
    }

    return three_sum;
}



/* Display the solutions */
std::string display_solution(const std::set<std::multiset<int>>& ans) 
{
       std::string str = "[";
    /* If the answer is not empty add
     * the multiset to the string */
    if(!ans.empty()) {
        for (const auto &triplet: ans) {
            if(ans.size()>1)
                str += "[";
            for (auto i: triplet)
                str += std::to_string(i) += ", ";
            str.resize(str.size()-2);  // remove the last ", " that was added
            if(ans.size()>1)
                str += "], ";
        }
        str.resize(str.size()-2);      // remove the last ", " that was added
    }
    str += "]";
    return str;
}



/* Driver code to test the function */
int main() {
    std::vector<int> nums = { -1,0,1,2,-1,-4 };
    /* Find and display the solution */
    std::cout << display_solution(find3Numbers(nums)) << std::endl;
    nums = { 7,2,1,12 };
    /* Find and display the solution */
    std::cout << display_solution(find3Numbers(nums)) << std::endl;
    nums = { -25,10,-10,8,-7,2,4,-3 };
    /* Find and display the solution */
    std::cout << display_solution(find3Numbers(nums)) << std::endl;
    return 0;
}
