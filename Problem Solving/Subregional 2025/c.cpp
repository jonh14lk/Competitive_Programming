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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

void multiply(vector<int> &v)
{
  vector<int> ot = {1, 1};
  vector<int> res(v.size() + ot.size() - 1);
  for (int i = 0; i < v.size(); i++)
  {
    for (int j = 0; j < ot.size(); j++)
      res[i + j] += v[i] * ot[j];
  }
  swap(res, v);
}
void divide(vector<int> &v)
{
  int num = 0;
  for (int i = 0; i < v.size(); i++)
  {
    num += (v[i] * (1ll << i));
  }
  num /= 2;
  vector<int> res;
  while (num)
  {
    res.pb(num % 2);
    num /= 2;
  }
  swap(res, v);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n + 1);
  for (int i = n; i >= 0; i--)
  {
    cin >> v[i];
  }
  int ans = 0;
  while (!(v.size() == 1 && v[0] == 1))
  {
    ans++;
    if (v[0] == 1)
    {
      multiply(v);
      v[0]++;
      for (auto &i : v)
      {
        if (i == 2)
          i = 0;
      }
    }
    else
    {
      divide(v);
    }
  }
  cout << ans << endl;
  return 0;
}