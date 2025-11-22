/* DP Prob. #30. Decibinary Numbers
This problem could be solved using three methods
Refer .odt doc for the solutions
*/

//  Method 1. Brute Force - Converting decibinary numbers from 0 to dmax to their decimal equivalent
//  and then sorting them in order of their decimal value.
//  Gets TLE for x > 50, hence need DP to reduce running time.
//  Running time = O(dmax*log10(i)+dmax*log2(dmax)) ~ O(dmax*log2(dmax))
//  Auxiliary space = O(dmax) due to the map mp

#include <bits/stdc++.h>
using namespace std;

long decBinToDec(long n) {
    long decVal = 0;
    int k = 0;
    while(n) {
        //decVal += (n%10)*pow(2, k++);
        decVal += (n%10)*(1<<k++);
        n = n/10;
    }
    return decVal;
}

long decibinaryNumbers(long x) {
    multimap<long, long> mp;
    long size = 100000;
    for(long i=0; i<=size; i++) {
        long decVal = decBinToDec(i);
        mp.insert({decVal, i});
    }
    map<long, long> mpCount;
    int k = 1;
    /*
    cout<<"S n0.\tDecimal\tDecibinary\n";
    for(auto i : mp) {
        cout<<k<<"\t"<<i.first<<"\t"<<i.second<<"\n";
        k++;
    }
    */
    k = 1;
    for(auto i : mp) {
        if(k==x) return i.second;
        k++;
    }
    return -1;
}

int main() {
    int t;
    cin>>t;
    while(t--) {
        long n;
        cin>>n;
        cout<<decibinaryNumbers(n)<<"\n";
    }
    return 0;
}

//  Method 2. Recursion without memoization (Top Down Approach) - Similar to no. of steps or coin change problem
//  Best solution to understand and remember
//  Creating decibinary number from decimal values. It takes care of multiple decibinary numbers being created
//  from the same decimal value. The function  is recursive. It takes three parameters, the number of digits d, the required
//  value s, and the current integer being built, v. At each point, we decide to place any digit from 0 to 9 as the dth digit;
//  we subtract the corresponding value from s and add the value of deciBinary component to v and then recurse to a smaller case.
//  Exactly when s becomes 0 and d becomes -1, we can just add v to our answer list else we don't add that v and backtrack.

//  Running time = O(upper_bound of s * 10^s * d) which is O(exponential*c) thus inefficient but still better than method 1 and works for n ~ 1e7
//  Auxiliary space = O(decibinary(600)) since the decimal 600 bounds the decibinary numbers upto 1e7

#include <iostream>
#include <vector>
using namespace std;

vector<int> ans;

void gen(int d, int s, int v) {                         //  d = max no. of digits here 20 due to long, s = decimal value
    if (s < 0 || s > 9*((1 << (d+1))-1)) return;        //  v = decibinary number being built from s
    else if (s == 0 && d == -1) ans.push_back(v);       //  It is exactly when s == 0 and d == -1 we can say that s is converted into its decibinary equivalent
    else {                                              //  else when s < 0 it does not have any decibinary equivalent
        for (int i = 0; i <= 9; i++)                    //  It is important for i to vary from 0 to 9, and d varies from 20 to 0, so that the
            gen(d-1, s-i*(1 << d), v*10+i);             //  decibinary numbers being built are already sorted by their intrinsic decimal values
    }
}

int main() {
    int val = 0, cur, q, x;
    for (int i = 0; i < 600; i++)       //  s is bounded by 600 to get decibinary numbers upto 10^7
        gen(20, i, 0);                  //  d is bounded by 20 due the max val of long being 2^63-1 ~ 10^19 i.e. 20 digits
    cin >> q;
    while (q--) {
        cin >> x;
        cout << ans[x-1] << '\n';
    }
}

//  Method 3. (Editor's Solution) DP + Cumulative array + Binary SearchDP where DP[d][s] = number of decibinary numbers of the same decimal value s
//  Yet to understand as skipped due to scarcity of time
//  Running time = O(ds + q(d+log10s))
//  Auxiliary space = O(ds)
//  Bounds for d = 25 and s = 300005
//  Passes all the test cases

#include <ios>
#include <iostream>

long long int dp[25][300005] = {};
long long int nm[300005] = {};

long long int cnt(int d, int s)
{
	if (d == -1 && s == 0)
		return 1;
	else if (d == -1)
		return 0;
	else if (dp[d][s] == -1)
	{
		dp[d][s] = 0;
		for (int i = 0; i <= 9 && (1 << d)*i <= s; i++)
			dp[d][s] += cnt(d-1, s-((1 << d)*i));
	}
	return dp[d][s];
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	for (int i = 0; i < 25; i++)
		for (int j = 0; j < 300005; j++)
			dp[i][j] = -1;
	for (int i = 0; i < 300005; i++)
		nm[i] = cnt(24, i);
	for (int i = 1; i < 300005; i++)
		nm[i] += nm[i-1];
	int q, lo, hi, ans;
	long long int x;

	std::cin >> q;
	while (q--)
	{
		std::cin >> x;
		if (x == 1)
			std::cout << 0 << '\n';
		else
		{
			lo = 0;
			hi = 300004;
			while (lo <= hi)
			{
				int mid = (lo+hi)/2;
				if (nm[mid] >= x)
				{
					ans = mid;
					hi = mid-1;
				}
				else
					lo = mid+1;
			}

			long long int g = x-nm[ans-1];
			long long int s = ans;
			long long int val;
			int d;

			for (int i = -1; cnt(i, s) < g; i++)
				d = i;
			d++;

			while (d >= 0)
			{
				val = 0;
				for (int i = 0; i <= 9; i++)
				{
					if ((s - (1 << d)*i) >= 0)
						val += cnt(d-1, s-(1 << d)*i);
					if (val >= g)
					{
						std::cout << i;
						g -= val-cnt(d-1, s-(1 << d)*i);
						s -= (1 << d)*i;
						break;
					}
				}
				d--;
			}
			std::cout << '\n';
		}
	}
}
