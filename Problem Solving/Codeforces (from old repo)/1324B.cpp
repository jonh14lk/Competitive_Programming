#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
#define MAXN 5001
 
int freq [MAXN] ;
int main()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int q ;
    cin >> q ;
 
    while (q--)
    {
        int n ;
        cin >> n ;
        vector <int> v(n) ;
        memset(freq , 0 , sizeof(freq));
 
        bool can = false ;
 
        for (int i = 0 ; i < n ; i++)
        {
            cin >> v[i] ;
            freq[v[i]]++ ;
 
            if (freq[v[i]] == 2 && v[i - 1] != v[i])
            {
                can = true ;
            }
            else if (freq[v[i]] >= 3)
            {
                can = true ;
            }
        }
 
        (can) ? cout << "YES\n" : cout << "NO\n" ;
    }
}
