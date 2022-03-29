#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class string>
using ordered_set = tree<string, null_type, less<string>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 2001
#define mod 1000000007

int bsgs(int a, int b, int m)
{
  if (a == 0 && b == 0)
    return 1;
  a %= m, b %= m;
  int k = 1, add = 0, g;
  while ((g = __gcd(a, m)) > 1) // fazer a e m serem coprimos
  {
    if (b == k)
      return add;
    if (b % g)
      return -1;
    b /= g, m /= g, ++add;
    k = (k * 1ll * a / g) % m;
  }
  int n = sqrt(m) + 1;
  int an = 1;
  for (int i = 0; i < n; i++)
    an = (an * 1ll * a) % m;
  unordered_map<int, int> vals;
  for (int q = 0, cur = b; q <= n; q++)
  {
    vals[cur] = q;
    cur = (cur * 1ll * a) % m;
  }
  for (int p = 1, cur = k; p <= n; p++)
  {
    cur = (cur * 1ll * an) % m;
    if (vals.count(cur))
    {
      int ans = n * p - vals[cur] + add;
      return ans;
    }
  }
  return -1;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int a, b, m;
    cin >> a >> b >> m;
    cout << bsgs(a, b, m) << endl;
  }
  return 0;
}
// menor x tal que: (a^x) % m = b % m
// a e m sao coprimos
// se não forem coprimos tem como tratar
// complexidade: sqrt(m)