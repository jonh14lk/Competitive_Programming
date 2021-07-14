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
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    pq.push(x);
  }
  if (n == 1)
  {
    cout << "N\n";
    return 0;
  }
  bool has = false, can = true;
  while (pq.size())
  {
    if (pq.size() == 2 && !has)
      break;
    if (pq.size() <= 1)
      break;
    int x = pq.top();
    pq.pop();
    int y = pq.top();
    pq.pop();
    if (x == y)
    {
      pq.push(x + 1);
    }
    else if (!has)
    {
      has = true;
      pq.push(y);
    }
    else
    {
      can = false;
      break;
    }
  }
  (can) ? cout << "Y\n" : cout << "N\n";
  return 0;
}