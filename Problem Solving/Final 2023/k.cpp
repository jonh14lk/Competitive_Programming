#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define MAXN 100005

int n, k;
int v[305];
int nxt[305][23];
int dp[1 << 21];
int par[1 << 21];

int solve()
{
  for (int mask = 0; mask < (1 << k); mask++)
  {
    dp[mask] = -1;
  }
  for (int mask = 0; mask < (1 << k); mask++)
  {
    for (int i = 0; i < k; i++)
    {
      if (mask & (1 << i))
      {
        int ot = (mask ^ (1 << i));
        if (dp[ot] == n)
        {
          par[mask] = i;
          dp[mask] = n;
          continue;
        }
        int eval = max(dp[mask], min(n, nxt[dp[ot] + 1][i]));
        if (dp[mask] < eval)
        {
          dp[mask] = eval;
          par[mask] = i;
        }
      }
    }
  }
  return dp[(1 << k) - 1] == n;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  cin >> n >> k;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
  }
  if (k <= 20)
  {
    for (int i = 0; i < n; i++)
    {
      v[i]--;
    }
    for (int x = 0; x < k; x++)
    {
      int nn = n;
      nxt[n][x] = n;
      for (int i = n - 1; i >= 0; i--)
      {
        if (v[i] == x)
          nn = i;
        nxt[i][x] = nn;
      }
    }
    if (!solve())
    {
      cout << "*\n";
      return 0;
    }
    int mask = (1 << k) - 1;
    vector<int> ans;
    for (int i = 0; i < k; i++)
    {
      int ot = mask ^ (1 << par[mask]);
      ans.pb(par[mask] + 1);
      mask = ot;
    }
    reverse(ans.begin(), ans.end());
    for (auto const &i : ans)
      cout << i << " ";
    cout << endl;
  }
  else
  {
    vector<int> aux;
    for (int i = 1; i <= k; i++)
    {
      aux.push_back(i);
    }
    while (1)
    {
      shuffle(aux.begin(), aux.end(), rng);
      int ptr = 0;
      for (int i = 0; i < n; i++)
      {
        if (ptr == k)
          break;
        if (aux[ptr] == v[i])
          ptr++;
      }
      if (ptr < k)
      {
        for (auto const &i : aux)
          cout << i << " ";
        cout << endl;
        return 0;
      }
    }
  }
}