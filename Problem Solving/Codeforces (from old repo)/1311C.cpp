#include <bits/stdc++.h>
using namespace std ;
 
#define pb push_back
#define lli long long int
 
int n , m , aux ;
string s ;
vector <int> v ;
vector<int> ans ;
 
int main ()
{ 
    int q ;
    cin >> q ;
 
    while (q--)
    {
        v.clear() ;
        ans.clear();
 
        cin >> n >> m ;
        cin >> s ;
 
        v.resize(n) ;
        ans.resize(26);
 
        for (int i = 0 ; i < m ; i++)
        {
            cin >> aux ;
            aux-- ;
            v[aux]++ ;
        } 

        for (int i = n - 1 ; i > 0 ; i--)
        {
            v[i - 1] += v[i] ; 
        }

        for (int i = 0 ; i < s.size() ; i++)
        {
            ans[s[i] - 'a'] += v[i] ; 
            ans[s[i] - 'a']++ ; 
        } 

        for (int i = 0 ; i < 26 ; i++)
        {
            cout << ans[i] << " " ;
        }

        cout << endl ;
    }
 
    return 0 ;
}
