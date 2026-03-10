#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

const int MAGIC = 180;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    int n, m;
    cin >> m >> n;
    int original_n = n, original_m = m;
    string s;
    vector<int> ways_at(MAGIC + 1, 0);
    vector<int> ways_ata(MAGIC + 1, 0);
    for (int i = 1; i <= MAGIC; i++)
    {
      ways_at[i] = i + ways_at[i - 1];
    }
    int sum_ap = 0;
    for (int i = 2; i <= MAGIC; i++)
    {
      sum_ap += (i - 1);
      ways_ata[i] = ways_ata[i - 1] + sum_ap;
    }
    vector<string> adj(MAGIC + 1, "");
    for (int i = MAGIC; i >= 1; i--)
    {
      while (n >= ways_at[i])
      {
        n -= ways_at[i];
        adj[i].pb('C');
      }
      while (i > 1 && m >= ways_ata[i])
      {
        m -= ways_ata[i];
        adj[i].pb('G');
      }
    }
    for (int i = 1; i <= MAGIC; i++)
    {
      s += "TA";
      s += adj[i];
    }
    reverse(s.begin(), s.end());
    cout << s << endl;
  }
  return 0;
}