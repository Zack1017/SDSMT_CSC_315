#include "algorithms.h"

#include <algorithm>
#include <queue>
#include <random>
#include <unordered_map>
#include <unordered_set>

//Greedy Algorithm
std::string reorganizeString(const std::string &s) 
{
    std::string result;
    std::unordered_map<char,int> freq;
    for (char c : s)
    {
        freq[c]++;
    }

    int n = (int)s.size();
    int maxFreq = 0;
    for (auto &p : freq) 
    {
        maxFreq = std::max(maxFreq, p.second);
    }

    if (maxFreq > (n + 1) / 2) 
    {
        return ""; //error
    }
    std::priority_queue<std::pair<int,char>> pq;
    for (auto &p : freq) 
    {
        pq.push({p.second, p.first});
    }

    std::pair<int,char> prev = {0, '#'};
    while (!pq.empty()) 
    {
        auto [cnt, ch] = pq.top();
        pq.pop();
        result.push_back(ch);
        cnt--;

        if (prev.first > 0) 
        {
            pq.push(prev);
        }
        prev = {cnt, ch};
    }

    if ((int)result.size() != n) 
    {
        return "";
    }
    return result;
}



//Divide & Conquer
namespace 
{ 
    std::string trimLeadingZeros(const std::string &bin) 
    {
        std::size_t pos = bin.find_first_not_of('0');
        if (pos == std::string::npos) 
        {
            return "0";
        }
        return bin.substr(pos);
    }



    std::string padLeft(const std::string &s, std::size_t len) 
    {
        if (s.size() >= len) 
        {
            return s;
        }
        return std::string(len - s.size(), '0') + s;
    }



    std::string addBinary(const std::string &a, const std::string &b) 
    {
        std::string A = a, B = b;
        std::string res;
        int i = (int)A.size() - 1;
        int j = (int)B.size() - 1;
        int carry = 0;

        while (i >= 0 || j >= 0 || carry) 
        {
            int bitA = (i >= 0 ? A[i--] - '0' : 0);
            int bitB = (j >= 0 ? B[j--] - '0' : 0);
            int sum = bitA + bitB + carry;
            res.push_back(char('0' + (sum & 1)));
            carry = sum >> 1;
        }
        std::reverse(res.begin(), res.end());
        return trimLeadingZeros(res);
    }



    std::string subBinary(const std::string &a, const std::string &b) 
    {
        std::string res;
        std::string A = a;
        std::string B = padLeft(b, a.size());
        int i = (int)A.size() - 1;
        int j = (int)B.size() - 1;
        int borrow = 0;

        while (i >= 0) 
        {
            int bitA = A[i] - '0';
            int bitB = (j >= 0 ? B[j] - '0' : 0);
            bitA -= borrow;
            if (bitA < bitB) 
            {
                bitA += 2;
                borrow = 1;
            } 
            else 
            {
                borrow = 0;
            }
            int diff = bitA - bitB;
            res.push_back(char('0' + diff));
            --i; 
            --j;
        }
        while (res.size() > 1 && res.back() == '0') 
        {
            res.pop_back();
        }
        std::reverse(res.begin(), res.end());
        return trimLeadingZeros(res);
    }



    std::string shiftLeft(const std::string &a, int k) 
    {
        if (a == "0") 
        {
            return "0";
        }
        return a + std::string(k, '0');
    }

    //Karatsuba
    std::string karatsubaCore(const std::string &x, const std::string &y) 
    {
        std::string a = trimLeadingZeros(x);
        std::string b = trimLeadingZeros(y);
        int n = (int)std::max(a.size(), b.size());
        if (n == 1) 
        {
            int p = (a[0] - '0') * (b[0] - '0');
            return p ? "1" : "0";
        }
        if (n % 2 != 0) 
        {
            n++;
        }
        a = padLeft(a, n);
        b = padLeft(b, n);
        int m = n / 2;
        std::string aHigh = a.substr(0, m);
        std::string aLow  = a.substr(m);
        std::string bHigh = b.substr(0, m);
        std::string bLow  = b.substr(m);
        std::string z0 = karatsubaCore(aLow, bLow);
        std::string z2 = karatsubaCore(aHigh, bHigh);
        std::string aSum = addBinary(aHigh, aLow);
        std::string bSum = addBinary(bHigh, bLow);
        std::string z1 = karatsubaCore(aSum, bSum);
        z1 = subBinary(z1, z2);
        z1 = subBinary(z1, z0);
        std::string part1 = shiftLeft(z2, 2 * m);
        std::string part2 = shiftLeft(z1, m);
        std::string res = addBinary(addBinary(part1, part2), z0);
        return trimLeadingZeros(res);
    }
} //namespace



std::string decToBin(long long x) 
{
    std::string res;
    if (x == 0) 
    {
        return "0";
    }
    while (x > 0) 
    {
        res.push_back((x & 1) ? '1' : '0');
        x >>= 1;
    }
    std::reverse(res.begin(), res.end());
    return res;
}



long long binToDec(const std::string &bin) 
{
    long long res = 0;
    for (char c : bin) 
    {
        res = res * 2 + (c - '0');
    }
    return res;
}



std::string karatsubaMultiplyBinary(const std::string &binA, const std::string &binB) 
{
    return karatsubaCore(binA, binB);
}



// Dynamic Programming
bool subsetSumDP(const std::vector<int> &arr, int sum) 
{
    int n = (int)arr.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(sum + 1, false));
    for (int i = 0; i <= n; ++i) 
    {
        dp[i][0] = true;
    }
    for (int i = 1; i <= n; ++i) 
    {
        for (int j = 1; j <= sum; ++j) 
        {
            if (arr[i - 1] > j) 
            {
                dp[i][j] = dp[i - 1][j];
            } 
            else 
            {
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            }
        }
    }
    return dp[n][sum];
}



//Randomized Algorithm 
int randomizedBinarySearch(const std::vector<int> &A, int x) 
{
    std::random_device rd;
    int left = 0;
    int right = (int)A.size() - 1;
    std::mt19937 gen(rd());
    while (left <= right) 
    {
        std::uniform_int_distribution<int> dist(left, right);
        int mid = dist(gen);
        if (A[mid] == x) 
        {
            return mid;
        } 
        else if (x < A[mid]) 
        {
            right = mid - 1;
        } 
        else 
        {
            left = mid + 1;
        }
    }
    return -1;
}



//Backtracking 
namespace 
{
    int hexToInt(char c) 
    {
        if (c >= '0' && c <= '9') 
        {
            return c - '0';
        }
        if (c >= 'A' && c <= 'F') 
        {
            return 10 + (c - 'A');
        }
        if (c >= 'a' && c <= 'f') 
        {
            return 10 + (c - 'a');
        }
        return 0;
    }



    int manhattanHeuristicInternal(const std::string &state) 
    {
        const std::string goal = "123456789ABCDEF0";
        int dist = 0;
        for (int i = 0; i < 16; ++i) 
        {
            char c = state[i];
            if (c == '0') 
            {
                continue;
            }
            int goalPos = (int)goal.find(c);
            int r1 = i / 4, c1 = i % 4;
            int r2 = goalPos / 4, c2 = goalPos % 4;
            dist += std::abs(r1 - r2) + std::abs(c1 - c2);
        }
        return dist;
    }

    struct NodeCompare 
    {
        bool operator()(const Node &a, const Node &b) const 
        {
            return (a.g + a.h) > (b.g + b.h);
        }
    };

    std::vector<std::pair<std::string,char>> neighbors(const std::string &s) 
    {
        std::vector<std::pair<std::string,char>> res;
        int pos = (int)s.find('0');
        int r = pos / 4, c = pos % 4;
        auto swapAndAdd = [&](int newR, int newC, char moveChar) 
        {
            int newPos = newR * 4 + newC;
            std::string t = s;
            std::swap(t[pos], t[newPos]);
            res.push_back({t, moveChar});
        };

        if (r > 0) 
        {
            swapAndAdd(r - 1, c, 'u');
        }
        if (r < 3) 
        {
            swapAndAdd(r + 1, c, 'd');
        }
        if (c > 0) 
        {
            swapAndAdd(r, c - 1, 'l');
        }
        if (c < 3) 
        {
            swapAndAdd(r, c + 1, 'r');
        }
    return res;
    
    }

} //namespace



bool isSolvable15(const std::string &state) 
{
    std::vector<int> vals;
    int blankRowFromTop = 0;
    int inversions = 0;
    for (int i = 0; i < 16; ++i) 
    {
        char c = state[i];
        if (c == '0') 
        {
            blankRowFromTop = i / 4;
        } 
        else 
        {
            vals.push_back(hexToInt(c));
        }
    }
    
    for (int i = 0; i < (int)vals.size(); ++i) 
    {
        for (int j = i + 1; j < (int)vals.size(); ++j) 
        {
            if (vals[i] > vals[j]) 
            {
                inversions++;
            }
        }
    }
    int rowFromBottom = 4 - blankRowFromTop;
    bool blankOddBottom = (rowFromBottom % 2 == 1);
    bool invEven = (inversions % 2 == 0);
    return (blankOddBottom && invEven) || (!blankOddBottom && !invEven);
}



bool solve15Puzzle(const std::string &start, std::string &pathOut) 
{
    std::unordered_set<std::string> visited;
    std::priority_queue<Node, std::vector<Node>, NodeCompare> pq;
    const std::string goal = "123456789ABCDEF0";
    if (start == goal) 
    {
        pathOut.clear();
        return true;
    }

    if (!isSolvable15(start)) 
    {
        return false;
    }
    
    Node startNode{start, 0, manhattanHeuristicInternal(start), ""};
    pq.push(startNode);
    while (!pq.empty()) 
    {
        Node cur = pq.top();
        pq.pop();
        if (visited.count(cur.state)) 
        {
            continue;
        }
        visited.insert(cur.state);
        if (cur.state == goal) 
        {
            pathOut = cur.path;
            return true;
        }

        for (auto &nb : neighbors(cur.state)) 
        {
            Node nxt;
            const std::string &nextState = nb.first;
            char moveChar = nb.second;
            if (visited.count(nextState)) 
            {
                continue;
            }
            nxt.state = nextState;
            nxt.g = cur.g + 1;
            nxt.h = manhattanHeuristicInternal(nextState);
            nxt.path = cur.path + moveChar;
            pq.push(nxt);
        }
    }
    return false;
}