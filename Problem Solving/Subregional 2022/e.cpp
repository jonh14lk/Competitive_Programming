#include <bits/stdc++.h>
using namespace std;

#define int long long int

int s[1000005];

signed main(){
    int n;
    cin >> n;
    int ans = n;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (s[x + 1] > 0)
        {
            s[x + 1]--;
            ans--;
        }
        s[x]++;
    }
    cout << ans << endl;
    return 0;
}