#include <bits/stdc++.h>
using namespace std;
 
#define pb push_back 
#define lli long long int
 
int main ()
{
    int n ;
    cin >> n ;
    string a ;
    cin >> a ;
 
    lli ans = 1 ;
    int lcont = 0 ;
    int rcont = 0 ;
 
    for (int i = 0 ; i < n ; i++)
    {
        if (a[i] == 'L')
        {
            lcont++ ;
        }
    }
 
    for (int i = 0 ; i < n ; i++)
    {
        if (a[i] == 'R')
        {
            rcont++ ;
        }
    }
 
    cout << rcont + lcont + 1 << endl ;
    
    return 0 ;
}
