#include <iostream>
#include <vector>
#include <string>
#include "algorithms.h"

// ===================== DEMO RUNS (AUTO) =====================

void demoGreedy() 
{
    std::cout << "\n--- Greedy Algorithm Demo: Reorganize String ---\n";
    std::string s = "aab";
    std::cout << "Input: " << s << "\n";
    std::string res = reorganizeString(s);
    if (res.empty())
        std::cout << "No valid rearrangement exists.\n";
    else
        std::cout << "Output: " << res << "\n";
}

void demoKaratsuba() 
{
    std::cout << "\n--- Divide & Conquer Demo: Karatsuba Multiplication ---\n";
    long long a = 12, b = 9;
    std::cout << "Input: " << a << " * " << b << "\n";

    std::string binA = decToBin(a);
    std::string binB = decToBin(b);
    std::string binProd = karatsubaMultiplyBinary(binA, binB);
    long long decProd = binToDec(binProd);

    std::cout << "Binary A: " << binA << "\n";
    std::cout << "Binary B: " << binB << "\n";
    std::cout << "Binary Product: " << binProd << "\n";
    std::cout << "Decimal Product: " << decProd << "\n";
}

void demoSubsetSum() 
{
    std::cout << "\n--- Dynamic Programming Demo: Subset Sum ---\n";
    std::vector<int> arr = {2, 3, 1, 1};
    int sum = 4;

    std::cout << "Array: 2 3 1 1\n";
    std::cout << "Target Sum: " << sum << "\n";

    bool possible = subsetSumDP(arr, sum);
    if (possible)
        std::cout << "Result: Subset EXISTS\n";
    else
        std::cout << "Result: No subset exists\n";
}

void demoRandomizedBinarySearch() 
{
    std::cout << "\n--- Randomized Algorithm Demo: Randomized Binary Search ---\n";
    std::vector<int> A = {1, 3, 5, 7, 9};
    int x = 7;

    std::cout << "Array: 1 3 5 7 9\n";
    std::cout << "Search for: " << x << "\n";

    int idx = randomizedBinarySearch(A, x);
    if (idx == -1)
        std::cout << "Result: Not found\n";
    else
        std::cout << "Result: Found at index " << idx << "\n";
}

void printBoard(const std::string &s) 
{
    for (int i = 0; i < 16; ++i) 
    {
        if (i % 4 == 0) std::cout << "\n";
        std::cout << s[i] << " ";
    }
    std::cout << "\n===========================\n";
}

void demo15Puzzle() 
{
    std::cout << "\n--- Backtracking Demo: 15 Puzzle Solver ---\n";
    std::string start = "123056789ABCDEF4";
    std::string path;

    std::cout << "Start Position: " << start << "\n";

    if (!solve15Puzzle(start, path)) 
    {
        std::cout << "No solution exists.\n";
        return;
    }

    std::cout << "Solution found in " << path.size() << " moves:\n";
    std::cout << path << "\n";

    std::string current = start;
    printBoard(current);

    for (char move : path) 
    {
        int pos = current.find('0');
        int r = pos / 4, c = pos % 4;
        int nr = r, nc = c;

        if (move == 'u') nr--;
        if (move == 'd') nr++;
        if (move == 'l') nc--;
        if (move == 'r') nc++;

        int newPos = nr * 4 + nc;
        std::swap(current[pos], current[newPos]);
        printBoard(current);
    }
}

// ===================== USER INTERACTIVE MENU =====================

void userMenu()
{
    int choice;
    while (true)
    {
        std::cout << "\n=== Programming Assignment 3 Menu ===\n";
        std::cout << "1. Greedy: Reorganize String\n";
        std::cout << "2. Divide & Conquer: Karatsuba\n";
        std::cout << "3. Dynamic Programming: Subset Sum\n";
        std::cout << "4. Randomized Algorithm: Binary Search\n";
        std::cout << "5. Backtracking: 15 Puzzle Solver\n";
        std::cout << "0. Exit\n";
        std::cout << "Select option: ";

        std::cin >> choice;

        if (!std::cin) return;

        switch (choice)
        {
            case 1:
            {
                std::string s;
                std::cout << "Enter string: ";
                std::cin >> s;
                std::cout << reorganizeString(s) << "\n";
                break;
            }
            case 2:
            {
                long long a, b;
                std::cout << "Enter two numbers: ";
                std::cin >> a >> b;
                std::string binA = decToBin(a);
                std::string binB = decToBin(b);
                std::string binProd = karatsubaMultiplyBinary(binA, binB);
                std::cout << "Result: " << binToDec(binProd) << "\n";
                break;
            }
            case 3:
            {
                int n, sum;
                std::cout << "Enter n: ";
                std::cin >> n;
                std::vector<int> arr(n);
                for (int i = 0; i < n; i++) std::cin >> arr[i];
                std::cout << "Enter sum: ";
                std::cin >> sum;
                std::cout << (subsetSumDP(arr, sum) ? "Exists\n" : "Does not exist\n");
                break;
            }
            case 4:
            {
                int n, x;
                std::cout << "Enter n: ";
                std::cin >> n;
                std::vector<int> arr(n);
                for (int i = 0; i < n; i++) std::cin >> arr[i];
                std::cout << "Search for: ";
                std::cin >> x;
                std::cout << "Index: " << randomizedBinarySearch(arr, x) << "\n";
                break;
            }
            case 5:
            {
                std::string start, path;
                std::cout << "Enter 16-char hex puzzle string: ";
                std::cin >> start;
                if (solve15Puzzle(start, path))
                    std::cout << "Solution: " << path << "\n";
                else
                    std::cout << "No solution.\n";
                break;
            }
            case 0:
                return;
            default:
                std::cout << "Invalid choice.\n";
        }
    }
}

// ===================== MAIN =====================

int main()
{
    std::cout << "\n===== AUTO-RUNNING ALL PDF EXAMPLES =====\n";

    demoGreedy();
    demoKaratsuba();
    demoSubsetSum();
    demoRandomizedBinarySearch();
    demo15Puzzle();

    std::cout << "\n===== ENTERING USER INTERACTIVE MODE =====\n";
    userMenu();

    return 0;
}
