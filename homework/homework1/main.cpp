#include <bits/stdc++.h>
using namespace std;

vector<int> calcEgyptianFractions(int num, int den, vector<int> denominators)
{
    // Base case: if numerator becomes 0, return the list of denominators
    if (num == 0)
        return denominators;
  
    // Find the smallest possible unit fraction denominator
    int unitDenominator = ceil((double)den / num);
  
    // Store the found denominator in the result
    denominators.push_back(unitDenominator);
  
    // Recurse with updated fraction (num/den - 1/unitDenominator)
    denominators = calcEgyptianFractions(
        num * unitDenominator - den,
        den * unitDenominator,
        denominators
    );
  
    return denominators;
}

string EgyptianFraction( int den,int num)
{
    cout << "Egyption Thingy of: " << num << "/" << den << " is" <<endl;
    string result = "";

    vector<int> dens = calcEgyptianFractions(num, den, {});
    
    // Construct string representation
    for (auto d : dens)
        result += "1/" + to_string(d) + " + ";
  
    // Remove the last " + "
    string finalResult = result.substr(0, result.length() - 3);
    return finalResult;
}

int main()
{
    cout << EgyptianFraction( 3, 2) << endl;
    cout << EgyptianFraction( 22, 7) << endl;
    cout << EgyptianFraction( 7, 3) << endl;
    cout << EgyptianFraction( 5, 4) << endl;
    cout << EgyptianFraction( 14, 6) << endl;
    return 0;
}
