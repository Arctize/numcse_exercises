#include <algorithm>
#include <bits/stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

float naive_sum(vector<float>& v)
{
    float sum = 0;
    for (float x : v) {
	sum += x;
    }
    return sum;
}

// b)
float sum(vector<float> v)
{
    float sum = 0;

    std::sort(v.begin(), v.end());
    for (float x : v) {
	sum += x;
    }

    return sum;
}

// d)
float acc_sum(vector<float>& v)
{
    float sum = 0;
    float acc = 0;
    float prev;
    for (float x : v) {
	prev = sum;
	sum += x;

	/* Idea:
		 Add the difference from between how much we tried 
		 to add, and how much we actually added, to a
		 seperate variable.
		 */
	acc += abs(x - (sum - prev));
    }
    return sum + acc;
}

int main()
{
    srand(time(0));
    cout << setprecision(15);
    int N = 1e7;
    double corr_sum = 0;
    vector<float> v(N);
    for (int i = 0; i < N; i++) {
	double x = 1e-8 + (rand() % 10) * 1e-9;
	corr_sum += x;
	v[i] = (float)x;
    }
    corr_sum += 1;
    v[1] = 1;

    cout << "naive_sum(v) = " << naive_sum(v) << endl
	 << "      sum(v) = " << sum(v) << endl
	 << "  acc_sum(v) = " << acc_sum(v) << endl
	 << " correct sum = " << corr_sum << endl;
}
