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
#define MAXN 101
#define mod 998244353

int grundy_num[MAXN][MAXN];

int mex(int i, int j)
{
  vector<bool> vis(1001, false);
  for (int k = 1; k <= max(i, j); k++)
  {
    if (i >= k)
      vis[grundy_num[i - k][j]] = true;
    if (j >= k)
      vis[grundy_num[i][j - k]] = true;
    if (i >= k && j >= k)
      vis[grundy_num[i - k][j - k]] = true;
  }
  for (int i = 0; i <= 1000; i++)
    if (!vis[i])
      return i;
}
void calc()
{
  for (int i = 0; i <= 100; i++)
  {
    for (int j = 0; j <= 100; j++)
      if (!i || !j || i == j)
        grundy_num[i][j] = 1000;
  }
  for (int i = 0; i <= 100; i++)
  {
    for (int j = 0; j <= 100; j++)
    {
      if (!i || !j || i == j)
        continue;
      grundy_num[i][j] = mex(i, j);
    }
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  calc();
  int x = 0;
  for (int i = 0; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    if (!a || !b || a == b)
    {
      x = 1;
      break;
    }
    x ^= grundy_num[a][b];
  }
  (x != 0) ? cout << "Y\n" : cout << "N\n";
  return 0;
}
// caso exista algum cara que chegue em (0,0) em 1 movimento
// tem que tratar isso, para dar a vitoria ao imperador nesse caso
// de resto a ideia eh
// atribuir um grundy number a cada uma das posições (i, j)
// o grundy number pode ser o mex, sabendo os grundy_numbers dos estados que posso atingir
// basicamente uma dp iterativa (dava pra ser dp recursiva tbm)
// depois ver se o xor dos grundy numbers da != 0
// como se fosse a ideia do nim msm