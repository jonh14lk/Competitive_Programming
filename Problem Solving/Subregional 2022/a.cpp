#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main(){
    int n;
    string s;
    cin >> n >> s;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] != 'a')
            continue;
        if (i - 1 >= 0 && s[i - 1] == 'a')
            ans++;
        else if (i + 1 < n && s[i + 1] == 'a')
            ans++;
    } 
    cout << ans << endl;
    return 0;
}