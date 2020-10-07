#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main() 
{
    lli n , m ;
    cin >> n >> m ;
 
    if (n == 0 && m == 0)
    {
        cout << "0\n" ;
    }
    else if (m % 2 != n % 2)
    {
        cout << "-1\n" ;
    }
    else if (n > m)
    {
        cout << "-1\n" ;
    }
    else if (n == m)
    {
        cout << "1\n" ;
        cout << n << endl ;
    }
    else
    {
        lli aux = (m - n) / 2 , ans1 = n ^ aux ; 
 
        if (n & aux)
        {
            cout << "3\n" ;
            cout << n << " " << aux << " " << aux << endl ;
        }
        else
        {
            cout << "2\n" ;
            cout << ans1 << " " << aux << endl ;
        }
    }
}
