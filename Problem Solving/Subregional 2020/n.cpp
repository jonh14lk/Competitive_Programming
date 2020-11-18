#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define DEBUG false
#define fir first
#define sec second
#define mod 1000000007
#define MAXN 10001

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

vector<int> v;
vector<pi> edges;
vector<pi> adj[MAXN];
set<int> ans;
set<int> done;

void prop(int n, int val)
{
  for (auto const &i : adj[n])
    v[i.fir] = v[i.fir] / pow(val, i.sec);
}
void primefactors(int curr, int n)
{
  int start = (ans.size()) ? *ans.rbegin() : 2;
  for (int i = start; i <= sqrt(n);)
  {
    if (n % i == 0)
    {
      while (n % i == 0)
        n = n / i;
      ans.insert(i);
      prop(curr, i);
      if (ans.size() == done.size())
        return;
    }
    (i == 2) ? i += 1 : i += 2;
  }
  if (n > 2)
  {
    ans.insert(n);
    prop(curr, n);
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int m, n, k;
  cin >> m >> n >> k;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < k; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].pb({b, c});
    edges.pb({a, b});
  }
  sort(edges.begin(), edges.end());
  for (int i = 0; i < k; i++)
  {
    done.insert(edges[i].fir);
    if (ans.size() < done.size())
      primefactors(edges[i].fir, v[edges[i].sec]);
  }
  for (auto const &i : ans)
  {
    cout << i;
    (i == *ans.rbegin()) ? cout << endl : cout << " ";
  }
  return 0;
}