#include <bits/stdc++.h>
using namespace std;

// #define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 10005
#define mod 998244353

pii mat[5005 * 5005][2];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pi> v(n);
  vector<int> x_ord(n);
  vector<int> y_ord(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
    x_ord[i] = i;
    y_ord[i] = i;
  }
  sort(x_ord.begin(), x_ord.end(), [&](int i, int j)
       { return v[i].fir < v[j].fir; });
  sort(y_ord.begin(), y_ord.end(), [&](int i, int j)
       { return v[i].sec < v[j].sec; });
  auto get_id = [&](int i, int j)
  {
    return (i * n) + j;
  };
  for (int i = 0; i < (n * n); i++)
  {
    mat[i][0].fir = -1;
    mat[i][1].fir = -1;
  }
  for (int i = 0; i < n; i++)
  {
    stack<int> st;
    for (auto const &j : x_ord)
    {
      if (v[j].fir < v[i].fir)
      {
        st.push(j);
      }
      if (v[j].fir > v[i].fir)
      {
        int dist = v[j].fir - v[i].fir;
        while (!st.empty() && (v[i].fir - v[st.top()].fir) < dist)
        {
          st.pop();
        }
        if (!st.empty() && (v[i].fir - v[st.top()].fir) == dist)
        {
          int a = get_id(i, st.top());
          int b = get_id(i, j);
          mat[a][0] = {b, {dist, i}};
          mat[b][0] = {a, {dist, i}};
        }
      }
    }
  }
  for (int i = 0; i < n; i++)
  {
    stack<int> st;
    for (auto const &j : y_ord)
    {
      if (v[j].sec < v[i].sec)
      {
        st.push(j);
      }
      if (v[j].sec > v[i].sec)
      {
        int dist = v[j].sec - v[i].sec;
        while (!st.empty() && (v[i].sec - v[st.top()].sec) < dist)
        {
          st.pop();
        }
        if (!st.empty() && (v[i].sec - v[st.top()].sec) == dist)
        {
          int a = get_id(st.top(), i);
          int b = get_id(j, i);
          mat[a][1] = {b, {dist, i}};
          mat[b][1] = {a, {dist, i}};
        }
      }
    }
  }
  vector<bool> vis(n * n, 0);
  vector<bool> aux(n, 0);
  vector<int> pass;
  bool valid = 0;
  long long int cost = 0;
  auto dfs = [&](auto &&self, int x, int par) -> void
  {
    vis[x] = 1;
    for (int k = 0; k < 2; k++)
    {
      auto [y, c] = mat[x][k];
      if (y == -1)
      {
        continue;
      }
      if (valid)
      {
        return;
      }
      if (!vis[y])
      {
        cost += 2ll * c.fir;
        pass.pb(c.sec);
        self(self, y, x);
      }
      else if (vis[y] && y != par) // cycle
      {
        cost += 2ll * c.fir;
        pass.pb(c.sec);
        valid = 1;
        return;
      }
    }
  };
  long long int ans = 0;
  for (int i = 0; i < (n * n); i++)
  {
    if (!vis[i])
    {
      pass.clear();
      cost = 0;
      valid = 0;
      dfs(dfs, i, 1);
      for (auto const &i : pass)
      {
        if (aux[i])
        {
          valid = 0;
          break;
        }
        aux[i] = 1;
      }
      for (auto const &i : pass)
      {
        aux[i] = 0;
      }
      if (valid)
      {
        ans = max(ans, cost);
      }
    }
  }
  cout << ans << endl;
  return 0;
}