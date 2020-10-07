#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back
#define lli long long int
 
lli n , l ;
vector <lli> v ;
 
int main()
{
	scanf("%lld%lld", &n , &l);
	lli aux ;
 
	for (int i = 0 ; i < n ; i++)
	{
		scanf("%lld", &aux);
		v.pb(aux);
	}
 
	sort (v.begin() , v.end());
 
	double distance = max(v[0] , (l - v[n - 1]));
 
	double distance2 = INT_MIN ;
 
	for (int i = 0 ; i < n - 1 ; i++)
	{
		if((v[i + 1] - v[i]) > distance2)
		{
			distance2 = (v[i + 1] - v[i]) ;
		}
	}
 
	printf("%.10lf\n", max(distance , (distance2) /  2));
	
	return 0;
}
