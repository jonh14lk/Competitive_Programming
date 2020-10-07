#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
 
vector<pair<int, int>> v;
vector<char> ans;
int main()
{
  int n, m, k;
  cin >> n >> m >> k;
 
  for (int i = 0; i < 2 * k; i++)
  {
    int a, b;
    cin >> a >> b;
    v.pb(make_pair(a, b));
  }
 
  for (int i = 0; i < n - 1; i++)
  {
    ans.pb('U');
  }
  for (int i = 0; i < m - 1; i++)
  {
    ans.pb('L');
  }
 
  for (int i = 0; i < n; i++)
  {
    if (i % 2 == 0)
    {
      for (int j = 0; j < m - 1; j++)
      {
        ans.pb('R');
      }
    }
    else
    {
      for (int j = 0; j < m - 1; j++)
      {
        ans.pb('L');
      }
    }
 
    if (i != n - 1)
    {
      ans.pb('D');
    }
  }
 
  cout << ans.size() << endl;
 
  for (int i = 0; i < ans.size(); i++)
  {
    cout << ans[i];
  }
 
  cout << endl;
 
  return 0;
}
