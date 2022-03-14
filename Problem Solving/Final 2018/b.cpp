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

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  int sum = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    sum += v[i];
  }
  if (sum % 2)
  {
    cout << "N\n";
    return 0;
  }
  for (int i = 0; i < n; i++)
  {
    v.pb(v[i]);
  }
  int j = 0, s = 0, t = 0, ok = sum / 2;
  for (int i = 0; i < n; i++)
  {
    while (j < v.size() && s < ok)
    {
      s += v[j];
      j++;
    }
    if (s == ok)
    {
      t++;
      if (t == 4)
      {
        cout << "Y\n";
        return 0;
      }
    }
    s -= v[i];
  }
  cout << "N\n";
}