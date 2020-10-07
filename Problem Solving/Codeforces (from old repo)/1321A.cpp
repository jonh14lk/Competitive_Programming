#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <int> v ;
vector <int> v2 ;
 
int main()
{
    int n ;
    cin >> n ;
 
    v.resize(n);
    v2.resize(n);
 
    int sum1 = 0 , sum2 = 0 , equals = 0 ;
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> v[i];
    }
 
    for (int i = 0 ; i < n ; i++)
    {
        cin >> v2[i];
    }
 
    for (int i = 0 ; i < n ; i++)
    {
        if (v[i] != v2[i])
        {
            sum1 += v[i];
            sum2 += v2[i];
        }
    }
 
    if (sum1 == 0)
    {
        cout << -1 << endl ;
    }
    else 
    {
        cout << (sum2 / sum1) + 1 << endl ;
    }
    
    return 0;
}
