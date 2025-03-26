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
#define MAXN 200005
#define mod 1000000007

int c[MAXN][4];
set<pi> st[4][4]; // quantos tem a quatidade x/pra quantos vai (profit dessa mudanca)

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    c[i][0] = 0;
    cin >> c[i][1] >> c[i][2] >> c[i][3];
    for (int j = 1; j <= 3; j++)
      st[0][j].insert({c[i][j] - c[i][0], i});
  }
  int ans = 0;
  auto rem = [&](int id, int val)
  {
    for (int j = 0; j <= 3; j++)
    {
      if (j != val)
        st[val][j].erase({c[id][j] - c[id][val], id});
    }
  };
  auto add = [&](int id, int val)
  {
    for (int j = 0; j <= 3; j++)
    {
      if (j != val)
        st[val][j].insert({c[id][j] - c[id][val], id});
    }
  };
  for (int tt = 0; tt < (3 * n); tt++)
  {
    int best = 1e18;
    vector<pii> op; // (indice, (antes, depois))
    for (int i = 0; i < 3; i++)
    {
      int j = i + 1;
      if (st[i][j].size() > 0)
      {
        pi aa = *st[i][j].begin();
        int curr = ans + aa.fir;
        if (curr < best)
        {
          best = curr;
          op.clear();
          op.pb({aa.sec, {i, j}});
        }
      }
    }
    for (int i = 0; i <= 3; i++)
    {
      for (int j = 0; j <= 3; j++)
      {
        for (int k = 0; k <= 3; k++)
        {
          for (int l = 0; l <= 3; l++)
          {
            if (i != j && l != k && ((j - i) + (l - k)) == 1)
            {
              if (st[i][j].size() == 0)
              {
                continue;
              }
              pi aa = *st[i][j].begin();
              pi bb = {-1, -1};
              for (auto const &dale : st[k][l])
              {
                if (dale.sec != aa.sec)
                {
                  bb = dale;
                  break;
                }
              }
              if (bb.fir == -1)
              {
                continue;
              }
              int curr = ans + aa.fir + bb.fir;
              if (curr < best)
              {
                best = curr;
                op.clear();
                op.pb({aa.sec, {i, j}});
                op.pb({bb.sec, {k, l}});
              }
            }
          }
        }
      }
    }
    for (int i = 0; i <= 3; i++)
    {
      for (int j = 0; j <= 3; j++)
      {
        for (int k = 0; k <= 3; k++)
        {
          for (int l = 0; l <= 3; l++)
          {
            for (int f = 0; f <= 3; f++)
            {
              for (int g = 0; g <= 3; g++)
              {
                if (i != j && l != k && f != g && ((j - i) + (l - k) + (g - f)) == 1)
                {
                  if (st[i][j].size() == 0)
                  {
                    continue;
                  }
                  pi aa = *st[i][j].begin();
                  pi bb = {-1, -1};
                  pi cc = {-1, -1};
                  for (auto const &dale : st[k][l])
                  {
                    if (dale.sec != aa.sec)
                    {
                      bb = dale;
                      break;
                    }
                  }
                  if (bb.fir == -1)
                  {
                    continue;
                  }
                  for (auto const &dale : st[f][g])
                  {
                    if (dale.sec != aa.sec && dale.sec != bb.sec)
                    {
                      cc = dale;
                      break;
                    }
                  }
                  if (cc.fir == -1)
                  {
                    continue;
                  }
                  int curr = ans + aa.fir + bb.fir + cc.fir;
                  if (curr < best)
                  {
                    best = curr;
                    op.clear();
                    op.pb({aa.sec, {i, j}});
                    op.pb({bb.sec, {k, l}});
                    op.pb({cc.sec, {f, g}});
                  }
                }
              }
            }
          }
        }
      }
    }
    ans = best;
    for (auto const &i : op)
    {
      rem(i.fir, i.sec.fir);
      add(i.fir, i.sec.sec);
    }
    cout << ans << endl;
  }
}