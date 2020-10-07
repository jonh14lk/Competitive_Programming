#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int 
#define pb push_back
 
int main ()
{
	int n , k , m , aux , sum = 0 , ans = INT_MAX ;
	cin >> n >> k >> m ;
 
	for (int i = 0 ; i < n - 1 ; i++)
	{
		cin >> aux ;
		sum += aux ;
	}
 
	for (int i = 0 ; i <= k ; i++)
	{
		if ((double)(sum + i) / n >= m)
		{
			ans = i ;
			break ;
		}
	}
 
	if (ans == INT_MAX)
	{
		cout << "-1" << endl ;
	}
	else
	{
		cout << ans << endl ;
	}
	
 
	return 0;
}
