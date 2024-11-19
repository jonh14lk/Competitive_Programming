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
#define MAXN 200007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, t;
  cin >> n >> t;
  vector<int> row(n);
  vector<int> col(n);
  for (int i = 0; i < n; i++)
  {
    row[i] = i;
    col[i] = i;
  }
  for (int ii = 0; ii < t; ii++)
  {
    char c;
    int i, j;
    cin >> c >> i >> j;
    i--, j--;
    if (c == 'R')
      swap(row[i], row[j]);
    else
      swap(col[i], col[j]);
  }
  vector<vector<int>> cycles_row, cycles_col;
  set<int> sizes;
  {
    vector<bool> vis(n, 0);
    for (int i = 0; i < n; i++)
    {
      if (!vis[i])
      {
        int sz = 0;
        vector<int> c;
        int x = i;
        while (1)
        {
          sz++;
          c.pb(x);
          vis[x] = 1;
          x = row[x];
          if (vis[x])
            break;
        }
        cycles_row.pb(c);
        sizes.insert(sz);
      }
    }
  }
  {
    vector<bool> vis(n, 0);
    for (int i = 0; i < n; i++)
    {
      if (!vis[i])
      {
        int sz = 0;
        vector<int> c;
        int x = i;
        while (1)
        {
          sz++;
          c.pb(x);
          vis[x] = 1;
          x = col[x];
          if (vis[x])
            break;
        }
        cycles_col.pb(c);
        sizes.insert(sz);
      }
    }
  }
  if (sizes.size() > 1)
  {
    cout << "*\n";
    return 0;
  }
  assert(cycles_row.size() == cycles_col.size());
  vector<vector<int>> ans(n, vector<int>(n));
  int m = cycles_col.size();    // quantos ciclos tem
  int k = cycles_col[0].size(); // qual o tamanho de um ciclo
  for (int i = 0; i < m; i++)
  {
    int ini_color = (i * k);
    for (int j = 0; j < m; j++)
    {
      for (int x = 0; x < k; x++)
      {
        for (int y = 0; y < k; y++)
        {
          int ii = cycles_row[i][x];
          int jj = cycles_col[j][y];
          int curr = ((x - y + k) % k) + 1 + ini_color;
          ans[ii][jj] = curr;
        }
      }
      ini_color = (ini_color + k) % n;
    }
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      cout << ans[i][j] << " ";
    cout << endl;
  }
  return 0;
}
// v[i][j] == v[row[i]][col[j]]
// mas nao basta achar qualquer matriz que satisfaca isso
// mas tbm tem que ver as que todos os elementos de uma linha e uma coluna formam uma permutation de tamanho n

// row[i] eh uma permutation, assim como col[i]
// entao se eu tenho ciclos
// i -> p[i] -> p[p[i]] -> ... -> i
// os ciclos em ambas as permutacoes tem que ter o mesmo tamanho
// ou seja nas duas permutaoes de tamamho n
// todos os ciclos tem que ser de tamanho x em uma e de tamanho x na outra

// dai, conseguimos o check pra saber se eh * ou nao
// mas como construir?

// 1 2 3 4
// 4 1 2 3
// 3 4 1 2
// 2 3 4 1