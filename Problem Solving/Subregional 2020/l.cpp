#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define DEBUG 1
#define MAXN 10001
#define mod 1000000007

signed main()
{
  int n, m;
  cin >> n >> m;
  char v[n][m];
  int cnt[n][m];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> v[i][j], cnt[i][j] = 0;
  int q;
  cin >> q;
  while (q--)
  {
    string s;
    cin >> s;
    int tam = s.size();
    vector<int> kappa(26, 0);
    for (int i = 0; i < s.size(); i++)
      kappa[s[i] - 'A']++;
    int curr[n][m];
    memset(curr, 0, sizeof(curr));
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (j + tam <= m)
        {
          vector<int> kappa2(26, 0);
          bool ok = true;
          for (int k = j; k < j + tam; k++)
            kappa2[v[i][k] - 'A']++;
          for (int k = 0; k < 26; k++)
            if (kappa[k] != kappa2[k])
              ok = false;
          if (ok)
            for (int k = j; k < j + tam; k++)
              curr[i][k] = 1;
        }
        if (i + tam <= n)
        {
          vector<int> kappa2(26, 0);
          bool ok = true;
          for (int k = i; k < i + tam; k++)
            kappa2[v[k][j] - 'A']++;
          for (int k = 0; k < 26; k++)
            if (kappa[k] != kappa2[k])
              ok = false;
          if (ok)
            for (int k = i; k < i + tam; k++)
              curr[k][j] = 1;
        }
        if (i + tam <= n && j + tam <= m)
        {
          vector<int> kappa2(26, 0);
          bool ok = true;
          for (int k = i, l = j; k < i + tam; k++, l++)
            kappa2[v[k][l] - 'A']++;
          for (int k = 0; k < 26; k++)
            if (kappa[k] != kappa2[k])
              ok = false;
          if (ok)
            for (int k = i, l = j; k < i + tam; k++, l++)
              curr[k][l] = 1;
        }
        if (i + tam <= n && j - tam >= -1)
        {
          vector<int> kappa2(26, 0);
          bool ok = true;
          for (int k = i, l = j; k < i + tam; k++, l--)
            kappa2[v[k][l] - 'A']++;
          for (int k = 0; k < 26; k++)
            if (kappa[k] != kappa2[k])
              ok = false;
          if (ok)
            for (int k = i, l = j; k < i + tam; k++, l--)
              curr[k][l] = 1;
        }
      }
    }
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        cnt[i][j] += curr[i][j];
  }
  int ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (cnt[i][j] >= 2)
        ans++;
  cout << ans << endl;
  return 0;
}