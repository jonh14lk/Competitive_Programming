#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main() 
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    int q ;
    cin >> q ;
 
    while (q--)
    {
        lli x , y , a , b ;
        cin >> x >> y >> a >> b ;
 
        lli dif = y - x ;
        lli sum = a + b ;
 
        if (dif >= sum && dif % sum == 0)
        {
            cout << dif / sum << endl ;
        }
        else
        {
            cout << "-1\n" ;
        }
        
    }
    return 0 ;
}
