#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

int min(long a, long b) {
    return (a < b) ? a : b;
}

int max(long a, long b) {
    return (a >= b) ? a : b;
}

long calc_combs_fast(vector<long> times, vector<long> distances)
{
    int n = times.size();
    vector<int> combs(n, 0);

    for (int i = 0; i < n; i++)
    {

        int a = 1;
        int comb;
        long b = -times[i];;
        long c = distances[i];

        double x1 = (-b + pow(pow(b, 2) - (4*a*c), 0.5)) * (0.5 * a);
        double x2 = (-b - pow(pow(b, 2) - (4*a*c), 0.5)) * (0.5 * a);

        comb = floor(max(x1, x2)) - ceil(min(x1, x2)) + 1;
        combs[i] = comb;
    }

    long product = 1;
    for (int i = 0; i < n; i++) { product *= combs[i]; }

    return product;
}

long calc_combs(vector<long> times, vector<long> distances)
{
    int n = times.size();
    vector<int> combs(n, 0);

    for (int i = 0; i < n; i++)
    {
        long t = times[i];
        long d = distances[i];
        int comb = 0;

        for (int j = 0; j < min(t, d); j++)
        {
            long total_distance = (t - j) * j;
            if (total_distance > d) {comb++;}
        }

        combs[i] = comb;
    }

    long product = 1;
    for (int i = 0; i < n; i++) { product *= combs[i]; }

    return product;
}

int main()
{
    vector<long> times;
    vector<long> distances;

    times = {46, 85, 75, 82};
    distances = {208, 1412, 1257, 1410};

    cout << "The answer for Day 6 Part 1 is: " << calc_combs_fast(times, distances) << endl;

    times = {46857582};
    distances = {208141212571410};

    cout << "The answer for Day 6 Part 2 is: " << calc_combs_fast(times, distances) << endl;

    return 0;
}