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
#define MAXN 200005
#define mod 1000000007

namespace dsu
{
  struct rollback
  {
    int u, v, rankv, ranku, time;
  };

  int num_sets;
  int parent[MAXN];
  int rank[MAXN];
  stack<rollback> op;

  int Find(int i)
  {
    return (parent[i] == i) ? i : Find(parent[i]);
  }
  bool Union(int x, int y, int time)
  {
    int xx = Find(x);
    int yy = Find(y);
    if (xx != yy)
    {
      num_sets--;
      if (rank[xx] > rank[yy])
        swap(xx, yy);
      op.push({xx, yy, rank[xx], rank[yy], time + 1});
      parent[xx] = yy;
      if (rank[xx] == rank[yy])
        rank[yy]++;
      return true;
    }
    return false;
  }
  void do_rollback()
  {
    if (op.empty())
      return;
    rollback x = op.top();
    op.pop();
    num_sets++;
    parent[x.v] = x.v;
    rank[x.v] = x.rankv;
    parent[x.u] = x.u;
    rank[x.u] = x.ranku;
  }
  void init(int n)
  {
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      rank[i] = 0;
    }
    num_sets = n;
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  dsu::init(n);
  int curr = 0;
  stack<int> checkpoints;
  for (int i = 0; i < m; i++)
  {
    string s;
    cin >> s;
    if (s[0] == 'u')
    {
      int a, b;
      cin >> a >> b;
      a--, b--;
      if (dsu::Union(a, b, curr))
        curr++;
      cout << dsu::num_sets << endl;
    }
    else if (s[0] == 'p')
    {
      checkpoints.push(curr);
    }
    else
    {
      curr = checkpoints.top();
      checkpoints.pop();
      while (!dsu::op.empty() && dsu::op.top().time > curr)
        dsu::do_rollback();
      cout << dsu::num_sets << endl;
    }
  }
  return 0;
}
// https://cp-algorithms.com/data_structures/deleting_in_log_n.html
// https://codeforces.com/edu/course/2/lesson/7/3/practice/contest/289392/problem/A
// union u v - unite two sets
// persist - create a checkpoint to which the structure can rollback later
// rollback - rollback to the latest checkpoint
