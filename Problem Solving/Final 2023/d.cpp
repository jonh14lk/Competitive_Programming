#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string s;
    cin >> s;
    map<string, int> mp;
    mp["*****"]++;
    for (int i = 1; i < n; i++)
    {
        string t;
        cin >> t;
        string tt;
        for (int j = 0; j < 5; j++)
        {
            if (s[j] == t[j])
                tt.push_back('*');
            else if (s.find(t[j]) != string::npos)
                tt.push_back('!');
            else
                tt.push_back('X');
        }
        mp[tt]++;
    }
    int q;
    cin >> q;
    while (q--)
    {
        string s;
        cin >> s;
        cout << mp[s] << endl;
    }
}