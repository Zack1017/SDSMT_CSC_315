#include "SubsetSum.h"

std::string brace_join(const std::multiset<int>& ms) 
{
    std::ostringstream oss;
    oss << "{";
    for (auto it = ms.begin(); it != ms.end(); ) 
    {
        oss << *it;
        if (++it != ms.end()) 
        {
            oss << ", ";
        }
    }
    oss << "}";
    return oss.str();
}



bool SubSetSum(std::multiset<int> S, int target) 
{
    // Base case: empty set
    if (S.empty()) 
    {
        return (target == 0);
    }

    //descending order
    auto it_last = std::prev(S.end());
    int el = *it_last;
    S.erase(it_last);
    bool left = SubSetSum(S, target);
    bool right = SubSetSum(S, target - el);
    return left || right;
}




void run_case(const std::multiset<int>& S, int target) 
{
    bool ok = SubSetSum(S, target);
    std::cout << "Elements from " << brace_join(S) << (ok ? " Can " : " Can Not ") << "sum to " << target << "\n";
}