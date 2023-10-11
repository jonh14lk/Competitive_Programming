#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define MAXN 1000005

int n, k;
int v[MAXN];
int nxt[MAXN];
int freq[MAXN];

int sum(int x)
{
  int ans = 0;
  while (x > 0)
  {
    ans += (x % 10);
    x /= 10;
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> k;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    freq[v[i]]++;
  }
  for (int i = 0; i < MAXN; i++)
  {
    nxt[i] = i - sum(i);
  }
  int ans = 0;
  for (int i = MAXN - 1; i > 0; i--)
  {
    k -= freq[i];
    freq[nxt[i]] += freq[i];
    if (k <= 0)
    {
      ans = i;
      break;
    }
  }
  cout << sum(ans) << endl;
}