#include <bits/stdc++.h>
using namespace std ;
 
#define lli long long int
#define pb push_back
 
int main() 
{   
    int q ;
    cin >> q ;
 
    while(q--)
    {
        string s ;
        cin >> s ;
 
        int ans = 0 , flag = 0 , last_one = INT_MAX;
 
        for (int i = 0 ; i < s.size() ; i++)
        {
            if (s[i] == '1' && flag == 2)
            {
                ans += ((i - 1) - last_one) ;
                last_one = i ;
                flag = 1 ;
            }   
            else if (s[i] == '1' && flag != 2)
            {
                flag = 1 ;
                last_one = i ;
            }
            else if (s[i] == '0' && flag == 1)
            {
                flag = 2 ;
            }
        }
 
        cout << ans << endl ;
    }
 
    return 0 ;
}
