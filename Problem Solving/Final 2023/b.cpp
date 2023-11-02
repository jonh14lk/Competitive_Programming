#include <bits/stdc++.h>
using namespace std;

#define int long long int

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int m = 3 * n;
    vector<int> v(m);
    map<int, int> cnt;
    for (int i = 0; i < m; i++)
    {
        cin >> v[i];
        cnt[v[i]]++;
    }
    bool ok = 1;
    for (auto const &i : cnt)
    {
        if (i.second % 3 != 0)
            ok = 0;
    }
    if (!ok)
        cout << "Y\n";
    else
        cout << "N\n";
}