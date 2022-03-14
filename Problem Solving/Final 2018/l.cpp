#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

vector<pi> qry[MAXN];
int ans[MAXN];
int mx[MAXN];
int b[MAXN];

int sum(int r)
{
  int ret = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1)
    ret += b[r];
  return ret;
}
void add(int idx, int delta)
{
  for (; idx < MAXN; idx = idx | (idx + 1))
    b[idx] += delta;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    qry[a].pb({b, i});
  }
  for (int i = 2; i < MAXN; i++)
  {
    mx[i] = -1;
  }
  for (int i = 2; i < MAXN; i++)
  {
    if (mx[i] == -1)
    {
      for (int j = i; j < MAXN; j += i)
        mx[j] = max(mx[j], i);
    }
    add(mx[i], 1);
    for (auto const &j : qry[i])
    {
      int k = j.fir, id = j.sec;
      ans[id] = sum(k);
    }
  }
  for (int i = 0; i < n; i++)
    cout << ans[i] << endl;
  return 0;
}
// fazer um crivao
// achar o maior fator primo de cada numero
// talvez responder as queries offline