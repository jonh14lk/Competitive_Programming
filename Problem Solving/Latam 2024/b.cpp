#include <bits/stdc++.h>
using namespace std;

// #define int long long int
#define pb push_back
#define MAXN 1505
#define pi pair<int, int>
#define fir first
#define sec second

int all, qt;
bitset<MAXN> bt[MAXN];
bitset<MAXN> dp[MAXN];
bitset<MAXN> x, aux;
int dale[MAXN];
bitset<MAXN> dale2[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  k++;
  for (int i = 0; i < n; i++)
  {
    string s;
    cin >> s;
    s.pb('1');
    for (int j = 0; j < k; j++)
    {
      bt[i][j] = s[j] - '0';
    }
  }
  for (int i = 0; i < k; i++)
  {
    dale[i] = -1;
  }
  vector<bool> on(n, 0);
  for (int j = 0; j < n; j++)
  {
    all++;
    x = bt[j];
    aux.reset();
    for (int i = k - 1; i >= 0; i--)
    {
      if (x[i])
      {
        if (dale[i] == -1)
        {
          qt++;
          dp[i] = x;
          dale[i] = j;
          on[j] = 1;
          dale2[i] = aux;
          dale2[i][j] = 1;
          break;
        }
        aux ^= dale2[i];
        x ^= dp[i];
      }
    }
  }
  if (all == qt)
  {
    cout << "*\n";
    return 0;
  }
  int guy = -1;
  for (int i = 0; i < n; i++)
  {
    if (!on[i])
    {
      guy = i;
    }
  }
  x = bt[guy];
  aux.reset();
  aux[guy] = 1;
  for (int i = k - 1; i >= 0; i--)
  {
    if (x[i])
    {
      aux ^= dale2[i];
      x ^= dp[i];
    }
  }
  vector<int> ids;
  for (int i = 0; i < n; i++)
  {
    if (aux[i])
      ids.pb(i);
  }
  vector<int> ans(n, 0);
  int h = ids.size() / 2;
  for (int i = 0; i < h; i++)
    ans[ids[i]] = 1;
  for (int i = h; i < ids.size(); i++)
    ans[ids[i]] = 2;
  for (int i = 0; i < n; i++)
    cout << ans[i];
  cout << endl;
  return 0;
}