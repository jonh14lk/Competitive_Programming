#include <bits/stdc++.h>

using namespace std;
#define int long long int
#define fir first
#define sec second
#define mod 1000000009

const int d = 256;

signed main() {
    int n, c;
    cin >> n >> c;
    vector<string> v(n);
    vector<int> p(n);
    unordered_map<int, int> mp;
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        int pos = -1;
        for(int j = 0; j < c; j++)
        {
            if (v[i][j] == '*')
            {
                pos = j;
            }
        }
        for (char j = 'a'; j <= 'z'; j++)
        {
            v[i][pos] = j;
            int h = 0;
            for (auto const &x : v[i])
            {
                h = (h * d) % mod;
                h = (h + x) % mod;
            }
            mp[h]++;
        }
        v[i][pos] = '*';
        p[i] = pos;
    }
    string ans = "";
    int mx = -1;
    for (int i = 0; i < n; i++)
    {
        int pos =  p[i];
        for (char j = 'a'; j <= 'z'; j++)
        {
            v[i][pos] = j;
            int h = 0;
            for (auto const &x : v[i])
            {
                h = (h * d) % mod;
                h = (h + x) % mod;
            }
            if (mp[h] > mx)
            {
                ans = v[i];
                mx = mp[h];
            }
            else if (mp[h] == mx && v[i] < ans)
            {
                ans = v[i];
                mx = mp[h];
            }
        }
    }
    cout << ans << " " << mx << endl;
}