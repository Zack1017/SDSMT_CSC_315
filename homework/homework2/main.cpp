#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>
#include <string>

double sqrt(double N, double x, double delta) 
{
    if (N < 0.0) 
    {
        return 0.0;
    }
    
    double xkp1 = 0.5 * (x + N / x);
    if (std::fabs(xkp1 - x) <= delta) 
    {
        return xkp1;
    }
    else 
    {
        return sqrt(N, xkp1, delta);
    }
    
}

int main() 
{
    std::vector<double> Ns = 
    {
        3.0, 11.0, 17.0, 19.0, 101.0,
        1009.0, 10007.0, 104729.0, 999983.0, 10000019.0
    };
    long duration = 0;   // keep track of time
    // Open CSV output
    std::ofstream csv("results.csv");
    csv << "N,avg_time_ns\n";

    for (double N : Ns) 
    {
        std::vector<long long> samples;
        samples.reserve(10);

        for (int i = 0; i < 10; ++i) 
        {
            auto start = std::chrono::high_resolution_clock::now();
            volatile double ans = sqrt(N,N/2, 0.00001);
            auto stop  = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
            samples.push_back(duration);
            (void)ans; // prevent optimizing away
        }

        long double sum = 0.0L;
        
        std::sort(samples.begin(), samples.end());
        csv  << N << ',' << duration << "\n";
    }

    csv.close();

    std::cout << "Wrote results.csv with columns:\n";
    return 0;
}
