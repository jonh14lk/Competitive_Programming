// essa solução não passava na hora da prova no BOCA, mas passa no codeforces
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long int

const __int128 mod = (1ll << 62) - 1;
const __int128 c = 1e11 + 3;

int cnt[400005];
int cnt2[400005];

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<int> cntt(k + 1, 0);
    vector<int> v(n);
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
        cntt[v[i]]++;
    }
    int ans = 0;
    int mn = 1e9;
    for (int i = 1; i <= k; i++)
    {
        mn = min(mn, cntt[i]);
    }
    auto rem = [&](int x)
    {
        cnt2[cnt[x]]--;
        cnt[x]--;
        cnt2[cnt[x]]++;
    };
    auto add = [&](int x)
    {
        cnt2[cnt[x]]--;
        cnt[x]++;
        cnt2[cnt[x]]++;
    };
    if (k <= 200)
    {
        unordered_map<int, int> mp;
        for (int i = 0; i < n; i++)
        {
            v[i]--;
        }
        int all_zero = 0;
        for (int i = 0; i < k; i++)
        {
            all_zero = (all_zero * (__int128)1 * c) % mod;
            all_zero = ((__int128)all_zero + 1) % mod;
        }
        mp[all_zero] = 0;
        int mx = 0;
        for (int i = 0; i < n; i++)
        {
            cnt[v[i]]++;
            mx = max(mx, cnt[v[i]]);
            int h = 0;
            for (int i = 0; i < k; i++)
            {
                int x = mx - cnt[i];
                h = (h * (__int128)1 * c) % mod;
                h = ((__int128)h + x + 1) % mod;
            }
            if (mp.find(h) == mp.end())
            {
                mp[h] = i + 1;
            }
            else
            {
                ans = max(ans, i - mp[h] + 1);
            }
        }
    }
    else
    {
        for (int t = mn; t >= 1; t--)
        {
            int sz = k * t;
            if (sz > n)
                break;
            for (int i = 0; i < sz; i++)
            {
                cnt[v[i]]++;
            }
            for (int i = 1; i <= k; i++)
            {
                cnt2[cnt[i]]++;
            }
            int l = 0, r = sz - 1;
            while (1)
            {
                if (cnt2[t] == k)
                {
                    cout << sz << endl;
                    return 0;
                }
                l++;
                r++;
                if (r >= n)
                {
                    break;
                }
                rem(v[l - 1]);
                add(v[r]);
                if (cnt2[t] == k)
                {
                    cout << sz << endl;
                    return 0;
                }
            }
            for (int i = 1; i <= k; i++)
            {
                cnt2[cnt[i]] = 0;
                cnt[i] = 0;
            }
        }
    }
    cout << ans << endl;
}