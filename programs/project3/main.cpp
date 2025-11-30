#include <iostream>
#include <vector>
#include <string>
#include "algorithms.h"

void runGreedy() 
{
    std::string s;
    std::cout << "Enter string to reorganize: ";
    std::cin >> s;
    std::string res = reorganizeString(s);
    if (res.empty()) 
    {
        std::cout << "No valid rearrangement exists.\n";
    } 
    else 
    {
        std::cout << "Reorganized string: " << res << "\n";
    }
}



void runKaratsuba() 
{
    long long a, b;
    std::cout << "Enter two non-negative decimal integers: ";
    std::cin >> a >> b;
    std::string binA = decToBin(a);
    std::string binB = decToBin(b);

    std::cout << "Binary A: " << binA << "\n";
    std::cout << "Binary B: " << binB << "\n";

    std::string binProd = karatsubaMultiplyBinary(binA, binB);
    long long decProd = binToDec(binProd);

    std::cout << "Binary product: " << binProd << "\n";
    std::cout << "Decimal product (may overflow if very large): " << decProd << "\n";
}



void runSubsetSum() 
{
    int n; 
    int sum; 
    std::cout << "Enter n (number of elements): ";
    std::cin >> n;
    std::vector<int> arr(n);
    std::cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; ++i) 
    {
        std::cin >> arr[i];
    }
    std::cout << "Enter target sum: ";
    std::cin >> sum;

    bool possible = subsetSumDP(arr, sum);
    if (possible) 
    {
        std::cout << "A subset with sum " << sum << " EXISTS.\n";
    } 
    else 
    {
        std::cout << "No subset with sum " << sum << " exists.\n";
    }
}



void runRandomizedBinarySearch() 
{
    int n; 
    int x; 
    std::cout << "Enter n (size of sorted array): ";
    std::cin >> n;
    std::vector<int> A(n);
    std::cout << "Enter " << n << " sorted integers: ";
    for (int i = 0; i < n; ++i) 
    {
        std::cin >> A[i];
    }
    std::cout << "Enter value to search for: ";
    std::cin >> x;
    int idx = randomizedBinarySearch(A, x);
    if (idx == -1) 
    {
        std::cout << x << " not found in array.\n";
    } 
    else 
    {
        std::cout << x << " found at index " << idx << " (0-based).\n";
    }
}



void printBoard(const std::string &s) 
{
    for (int i = 0; i < 16; ++i) 
    {
        if (i % 4 == 0) 
        {
            std::cout << "\n";
        }
        std::cout << s[i] << " ";
    }
    std::cout << "\n===========================\n";
}



void run15Puzzle() 
{
    std::string start;
    std::string path;
    std::cout << "Example: 123056789ABCDEF4\n";
    std::cout << "Enter start position as 16 hex characters (0-F), row-major: ";
    std::cin >> start;
    if (start.size() != 16) 
    {
        std::cout << "Invalid input length.\n";
        return;
    }

    if (!solve15Puzzle(start, path)) 
    {
        std::cout << "No solution (unsolvable puzzle).\n";
        return;
    }
    std::cout << "Solution found in " << path.size() << " moves:\n";
     std::cout << path << "\n";

    std::string current = start;
    printBoard(current);
    for (char move : path) 
    {
        int pos = (int)current.find('0');
        int r = pos / 4, c = pos % 4;
        int nr = r, nc = c;
        if (move == 'u') 
        {
            nr--;
        }
        else if (move == 'd') 
        {
            nr++;
        }
        else if (move == 'l') 
        {
            nc--;
        }
        else if (move == 'r') 
        {
            nc++;
        }
        int newPos = nr * 4 + nc;
        std::swap(current[pos], current[newPos]);
        printBoard(current);
    }
}



int main() 
{
    int choice;
    while (true) 
    {
        std::cout << "\n=== Programming Assignment 3 Demo ===\n";
        std::cout << "1. greedy: Reorganize String\n";
        std::cout << "2. Divie & Conquer: Karatsuba (Binary)\n";
        std::cout << "3. Dynamic Programming: Subset Sum\n";
        std::cout << "4. Randomized Algorithm:   Randomized Binary Search\n";
        std::cout << "5. Backtracking:15 Puzzle Solver\n";
        std::cout << "0. Exit\n";
        std::cout << "Select option: ";
        
        if (!(std::cin >> choice)) 
        {
            break;
        }
        switch (choice) 
        {
            case 1: runGreedy(); 
                break;
            case 2: runKaratsuba(); 
                break;
            case 3: runSubsetSum(); 
                break;
            case 4: runRandomizedBinarySearch(); 
                break;
            case 5: run15Puzzle(); 
                break;
            case 0: return 0;
            default: std::cout << "Invalid option.\n"; break;
        }
    }
    return 0;
}
