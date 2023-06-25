#include <bits/stdc++.h>
using namespace std;

int main()
{
  int r, c, k;
  cin >> r >> c >> k;
  vector<int> cnt(r + 1, 0);
  for (int i = 0; i < c; i++)
  {
    int x;
    cin >> x;
    cnt[x]++;
  }
  sort(cnt.begin(), cnt.end());
  reverse(cnt.begin(), cnt.end());
  int ans = 0;
  for (int i = 0; i < min(k, r + 1); i++)
    ans += cnt[i];
  cout << ans << endl;
};