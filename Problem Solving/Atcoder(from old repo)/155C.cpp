#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
vector <string> v ;
set <string> s ;
map <string , int> m ;
vector <string> ans ;
 
int main ()
{
    int n ;
    cin >> n ;
    int c = 0 ;
 
    for (int i = 0 ; i < n ; i++)
    {
        string r ;
        cin >> r ;
 
        if (s.find(r) == s.end())
        {
            s.insert(r);
            m.insert(make_pair(r , 1));
            v.pb(r);
        }
        else
        {
            m[r] += 1 ;
        }
    }
 
    int mq = 0 ;
 
 
    for (int i = 0 ; i < v.size() ; i++)
    {
        if (m[v[i]] > mq)
        {
            ans.clear();
            ans.pb(v[i]);
            mq = m[v[i]] ;
        }
        else if (m[v[i]] == mq)
        {
            ans.pb(v[i]);
        }
    }
 
    sort(ans.begin() , ans.end()) ;
 
    for (int i = 0 ; i < ans.size() ; i++)
    {
        cout << ans[i] << endl ;
    }
 
    return 0 ;
}
