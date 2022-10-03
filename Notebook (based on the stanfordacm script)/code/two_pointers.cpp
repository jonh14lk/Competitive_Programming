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
#define MAXN 3005
#define mod 1000000007

const int inf = LLONG_MAX;
stack<pii> s[2];

void add(int x, int i)
{
  int mn = inf, mx = -inf;
  if (!s[i].empty())
  {
    mn = min(mn, s[i].top().sec.fir);
    mx = max(mx, s[i].top().sec.sec);
  }
  mn = min(mn, x);
  mx = max(mx, x);
  s[i].push({x, {mn, mx}});
}
void change()
{
  while (!s[1].empty())
  {
    int x = s[1].top().fir;
    s[1].pop();
    add(x, 0);
  }
}
void rem()
{
  if (!s[0].size())
    change();
  s[0].pop();
}
int q()
{
  int mn = inf, mx = -inf;
  for (int i = 0; i < 2; i++)
  {
    if (!s[i].empty())
    {
      mn = min(mn, s[i].top().sec.fir);
      mx = max(mx, s[i].top().sec.sec);
    }
  }
  if (mn == inf)
    return 0;
  return mx - mn;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  int ans = 0, i = 0;
  for (int j = 0; j < n; j++)
  {
    add(v[j], 1);
    while (q() > k)
    {
      rem();
      i++;
    }
    ans += (j - i + 1);
  }
  cout << ans << endl;
  return 0;
}
// https://codeforces.com/edu/course/2/lesson/9/2/practice/contest/307093/problem/F
// Given an array of n integers, Let's say that a segment of this array is good
// if the difference between the maximum and minimum elements on this segment is at most k
// Your task is to find the number of different good segments
// amazing trick using stack