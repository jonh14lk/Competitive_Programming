#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 501
#define MAXL 20
#define mod 998244353

int n;
vector<int> bit;
int sum(int r)
{
  int ret = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1)
    ret += bit[r];
  return ret;
}
void add(int idx, int delta)
{
  for (; idx < n; idx = idx | (idx + 1))
    bit[idx] += delta;
}
signed main()
{
  cin >> n;
  vector<int> v(n);
  bit.assign(n, 0);
  for (int i = 0; i < n; i++)
    cin >> v[i], add(i, v[i]);
  int q;
  cin >> q;
  while (q--)
  {
    char t;
    cin >> t;
    if (t == 'Q') // query
    {
      int l, r;
      cin >> l >> r;
      cout << (sum(r) - sum(l - 1)) << endl;
    }
    else // update
    {
      int a, b;
      cin >> a >> b;
      add(a, b - v[a]);
    }
  }
  return 0;
}
