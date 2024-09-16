#include <bits/stdc++.h>

using namespace std;

// #define int long long int
#define pi pair<int, int>
#define fir first
#define sec second

int n;
int a[105];
int dp[105][5005];
int c[105][5005];

int solve(int i, int j)
{
  if (j == 0)
    return 1;
  if (i == n)
    return 0;
  if (dp[i][j] != -1)
    return dp[i][j];
  int ans = solve(i + 1, j);
  c[i][j] = 0;
  if (j - a[i] >= 0)
  {
    int curr = solve(i + 1, j - a[i]);
    if (curr > ans)
    {
      c[i][j] = 1;
      ans = curr;
    }
  }
  return dp[i][j] = ans;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  int sum = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    sum += a[i];
  }
  memset(dp, -1, sizeof(dp));
  if (sum & 1)
  {
    cout << "-1\n";
    exit(0);
  }
  int ans = solve(0, sum / 2);
  if (!ans)
  {
    cout << "-1\n";
    exit(0);
  }
  int i = 0, j = sum / 2;
  vector<int> va, vb;
  while (i < n)
  {
    int op = c[i][j];
    if (op == 1)
    {
      vb.push_back(a[i]);
      j -= a[i];
      i++;
    }
    else
    {
      va.push_back(a[i]);
      i++;
    }
  }
  sort(va.rbegin(), va.rend());
  sort(vb.rbegin(), vb.rend());
  i = 0, j = 0;
  int suma = 0, sumb = 0;
  for (int x = 0; x < n; x++)
  {
    if (suma <= sumb)
    {
      suma += va[i];
      cout << va[i] << " ";
      i++;
    }
    else
    {
      sumb += vb[j];
      cout << vb[j] << " ";
      j++;
    }
  }
  cout << endl;
  return 0;
}