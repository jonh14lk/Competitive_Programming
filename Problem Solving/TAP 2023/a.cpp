#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  priority_queue<pi> pq;
  for (int i = 0; i < n; i++)
  {
    int x;
    cin >> x;
    pq.push({x, i});
  }
  while (m--)
  {
    int x;
    cin >> x;
    while (pq.top().fir >= x)
    {
      auto [y, i] = pq.top();
      pq.pop();
      y %= x;
      pq.push({y, i});
    }
  }
  vector<int> ans(n);
  while (!pq.empty())
  {
    ans[pq.top().sec] = pq.top().fir;
    pq.pop();
  }
  for (auto const &i : ans)
    cout << i << " ";
  cout << endl;
  return 0;
}