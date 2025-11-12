#ifndef SUBSETSUM_H
#define SUBSETSUM_H
#include <set>
#include <string>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

std::string brace_join(const std::multiset<int>& ms);

// Recursive
bool SubSetSum(std::multiset<int> S, int target);

void run_case(const std::multiset<int>& S, int target);

#endif // SUBSETSUM_H
