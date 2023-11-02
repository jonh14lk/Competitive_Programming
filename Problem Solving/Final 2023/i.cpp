#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define mod 1000000007

int solve(string &s)
{
    vector<int> mp(27, 0);
    int ans = 0;
    for (auto const &i : s)
    {
        int pos = i - 'a';
        for (int j = pos + 1; j < 27; j++)
            ans += mp[j];
        mp[i - 'a']++;
    }
    return ans;
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    int n;
    cin >> s >> n;
    map<char, int> mp;
    int sum = 0;
    for (auto const &i : s)
    {
        mp[i]++;
        sum++;
    }
    int ans = 0;
    for (auto const &i : mp)
    {
        sum -= i.second;
        __int128 qt = ((__int128)i.second * sum) % mod;
        __int128 pa = ((__int128)n * (n - 1)) / 2;
        pa %= mod;
        qt *= pa;
        qt %= mod;
        ans += qt;
        ans %= mod;
    }
    __int128 inv = solve(s);
    inv %= mod;
    inv *= n;
    inv %= mod;
    ans += inv;
    ans %= mod;
    cout << ans << endl;
}