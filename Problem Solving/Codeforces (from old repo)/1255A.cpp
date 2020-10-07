#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
 
int main() {
    int q;
    cin >> q;
    while(q--) 
    {
        lli a, b, ans = 0;
 
        scanf("%lld%lld", &a , &b);
        lli dif;
        if(a > b) dif = a - b;
        else dif = b - a;
 
        if(dif >= 5) 
        {
            if (dif % 5 == 0)
            {
                ans += dif / 5;
                dif = 0;
            }
            else
            {
                ans += dif/5;
                dif = dif % 5;
            }
        }
 
        if(dif >= 2) 
        {
            if (dif % 2 == 0)
            {
                ans += dif / 2 ;
                dif = 0;
            }
            else
            {
                ans += dif/2;
                dif = dif % 2 ;
            }   
        }
 
        if(dif == 1)
        {
            ans++;
        }
 
        printf("%lld\n", ans);
    }
    return (0);
}
