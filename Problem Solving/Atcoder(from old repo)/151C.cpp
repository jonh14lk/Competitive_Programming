#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int 
#define pb push_back
 
struct q 
{
	int at ;
	bool cor ;
};
int main ()
{
	int n , m , a , ans = 0 , ans2 = 0 ;
	cin >> n >> m ;
	string b ;
	struct q que [100001] ;
 
	for (int i = 0 ; i < 100001 ; i++)
	{
		que[i].at = 0 ;
		que[i].cor = false ;
	}
 
	for (int i = 0 ; i < m ; i++)
	{
		cin >> a >> b ;
 
		if (b == "AC" && !(que[a].cor))
		{
			que[a].cor = true ;
			ans += que[a].at ;
			ans2++ ;
		}
		else if (b == "WA")
		{
			que[a].at += 1 ;
		}
	}
 
	cout << ans2 ;
	cout << " " ;
	cout << ans << endl ;
 
	return 0;
}
