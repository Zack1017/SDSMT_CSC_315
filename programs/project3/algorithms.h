#pragma once

#include <string>
#include <vector>

struct Node {
    std::string state;
    int g;
    int h;
    std::string path;
};

//greedy
std::string reorganizeString(const std::string &s);

//Karatsuba
std::string decToBin(long long x);
long long   binToDec(const std::string &bin);
std::string karatsubaMultiplyBinary(const std::string &binA, const std::string &binB);

//Dynamic Programming
bool subsetSumDP(const std::vector<int> &arr, int sum);

//Randomized Algorithm 
int randomizedBinarySearch(const std::vector<int> &A, int x);

//Backtracking
bool solve15Puzzle(const std::string &start, std::string &pathOut);
bool isSolvable15(const std::string &state);
