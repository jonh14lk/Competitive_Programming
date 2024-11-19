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
#define MAXN 200007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  vector<int> pos(n + 1, -1);
  vector<int> pref(n + 1, 0);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    if (v[i] != 0)
    {
      pos[v[i]] = i;
      pref[i + 1] = pref[i] + 1;
    }
    else
    {
      pref[i + 1] = pref[i];
    }
  }
  auto get_sum = [&](int l, int r)
  {
    if (l > r)
      return 0ll;
    return pref[r + 1] - pref[l];
  };
  int l = 0, r = n - 1;
  queue<int> q;
  vector<int> ans(n);
  for (int i = 1; i <= n; i++)
  {
    if (pos[i] == -1)
    {
      q.push(i);
    }
    else if (pos[i] >= l && (pos[i] - l) <= q.size() &&
             get_sum(l, pos[i] - 1) == 0 &&
             get_sum(r - (q.size() - (pos[i] - l)) + 1, r) == 0)
    {
      while (l < pos[i])
      {
        ans[l] = q.front();
        l++;
        q.pop();
      }
      ans[l] = i;
      l++;
      while (q.size() > 0)
      {
        ans[r] = q.front();
        r--;
        q.pop();
      }
    }
    else if (pos[i] <= r && (r - pos[i]) <= q.size())
    {
      while (r > pos[i])
      {
        ans[r] = q.front();
        r--;
        q.pop();
      }
      ans[r] = i;
      r--;
      while (q.size() > 0)
      {
        ans[l] = q.front();
        l++;
        q.pop();
      }
    }
    else
    {
      cout << "*\n";
      return 0;
    }
  }
  while (q.size() > 0)
  {
    ans[l] = q.front();
    l++;
    q.pop();
  }
  for (auto const &i : ans)
  {
    cout << i << " ";
  }
  cout << endl;
  return 0;
}