#include <bits/stdc++.h>
using namespace std ;
 
#define pb push_back
#define lli long long int
 
int n , m ;
vector <int> v ;
vector <int> v2 ;
 
bool is_sorted ()
{
    for (int i = 0 ; i < n - 1 ; i++)
    {
        if (v[i] > v[i + 1])
        {
            return false ;
        }
    }
 
    return true ;
}
int main ()
{ 
    int q ;
    cin >> q ;
 
    while (q--)
    {
        v2.clear();
        v.clear();
 
        int aux ;
        cin >> n >> m ;
 
        for (int i = 0 ; i < n ; i++)
        {
            cin >> aux ;
            v.pb(aux);
        }
 
        for (int i = 0 ; i < m ; i++)
        {
            cin >> aux ;
            v2.pb(aux);
        }
 
        int j = 0 ;
 
        while (1)
        {
            if (j == m)
            {
                break ;
            }
            else if (v[v2[j] - 1] > v[v2[j]])
            {
                aux = v[v2[j] - 1] ;
                v[v2[j] - 1] = v[v2[j]];
                v[v2[j]] = aux ;
 
                j = -1 ;
            }
 
            j++ ;
        }
 
        (is_sorted()) ? cout << "YES\n" : cout << "NO\n" ;
    }
 
    return 0 ;
}
