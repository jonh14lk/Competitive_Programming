#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pb push_back

signed main()
{
  string s;
  int k;
  cin >> s >> k;
  vector<string> adj(k);
  for (int i = 0; i < s.size(); i++)
  {
    adj[i % k].pb(s[i]);
  }
  for (int i = 0; i < k; i++)
  {
    sort(adj[i].begin(), adj[i].end());
  }
  vector<int> ptr(k, 0);
  for (int i = 0; i < s.size(); i++)
  {
    cout << adj[i % k][ptr[i % k]];
    ptr[i % k]++;
  }
  cout << endl;
}