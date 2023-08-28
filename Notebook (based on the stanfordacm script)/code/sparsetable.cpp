#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
 
template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
#define PI acos(-1)
#define pb push_back
#define int long long int
#define pi pair<int, int>
#define pii pair<int, pair<int, pi>>
#define fir first
#define sec second
#define DEBUG 0
#define MAXN 10005
#define mod 1000000007
 
struct rmq
{
  bool is_min;
  vector<vector<int>> st;
  vector<int> log;
 
  int f(int a, int b) { return (is_min) ? min(a, b) : max(a, b); }
  int qry(int l, int r) { return f(st[l][log[r - l + 1]], st[r - (1 << log[r - l + 1]) + 1][log[r - l + 1]]); }
  rmq(vector<int> &v, bool flag)
  {
    is_min = flag;
    int n = v.size();
    log.resize(n + 1);
    log[1] = 0;
    for (int i = 2; i <= n; i++)
      log[i] = log[i / 2] + 1;
    int m = log[n] + 2;
    st.assign(n + 1, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
      st[i][0] = v[i];
    for (int j = 1; j < m; j++)
    {
      for (int i = 0; i + (1 << j) <= n; i++)
        st[i][j] = f(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}
