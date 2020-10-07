#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
int main()
{
    ios_base::sync_with_stdio(false) ; 
    cin.tie(NULL) ;
 
    int q ;
    cin >> q ;
 
    while (q--)
    {
        string s ;
        cin >> s ;
        int count = 0 , at = 0 ;
 
        if (s.size() == 1)
        {
            if (s[0] == 'L')
            {
                cout << "2\n" ;
            }
            else 
            {
                cout << "1\n" ;
            }
        }
        else
        {
            for (int i = 0 ; i < s.size() ; i++)
            {
                if (s[i] == 'L')
                {
                    at++ ;
                }
                else if (s[i] == 'R')
                {
                    count = max(at , count);
                    at = 0 ;
                }
            }
 
            count = max(at , count) ;
            cout << count + 1 << endl ;
        }
    }
}
