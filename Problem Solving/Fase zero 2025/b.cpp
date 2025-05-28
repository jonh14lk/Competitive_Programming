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
#define MAXN 100005

int par[MAXN];
char ch[MAXN];
vector<pair<int, char>> adj[MAXN];
int p[MAXN];
int aut[MAXN][26];
string st;

int add(char c)
{
  st.pb(c);
  int i = st.size() - 1;
  for (int c = 0; c < 26; c++)
  {
    if (i > 0 && 'a' + c != st[i])
      aut[i][c] = aut[p[i - 1]][c];
    else
      aut[i][c] = i + ('a' + c == st[i]);
  }
  if (i == 0)
  {
    p[i] = 0;
    return 0;
  }
  p[i] = aut[p[i - 1]][c - 'a'];
  int k = st.size() - p[i];
  if (st.size() % k == 0)
    return (k == st.size()) ? 0 : k; // tem que ser repetida pelo menos 2x
  return 0;
}
int dfs(int s)
{
  int ans = 0;
  for (auto const &i : adj[s])
  {
    ans = max(ans, add(i.sec));
    ans = max(ans, dfs(i.fir));
    st.pop_back();
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    cin >> par[i];
    par[i]--;
  }
  for (int i = 1; i < n; i++)
  {
    cin >> ch[i];
    adj[par[i]].pb({i, ch[i]});
  }
  cout << dfs(0) << endl;
  return 0;
}
