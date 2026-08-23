#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  deque<char> dq;
  int fa = 0, fb = 0, ans = 0;
  while (q--)
  {
    int op;
    cin >> op;
    if (op == 1)
    {
      char c;
      cin >> c;
      dq.pb(c);
      if (c == 'A')
      {
        fa++;
      }
      else
      {
        ans += fa;
        fb++;
      }
    }
    else if (op == 2)
    {
      char c;
      cin >> c;
      dq.push_front(c);
      if (c == 'A')
      {
        ans += fb;
        fa++;
      }
      else
      {
        fb++;
      }
    }
    else if (op == 3)
    {
      char c = dq.back();
      dq.pop_back();
      if (c == 'A')
      {
        fa--;
      }
      else
      {
        ans -= fa;
        fb--;
      }
    }
    else
    {
      char c = dq.front();
      dq.pop_front();
      if (c == 'A')
      {
        ans -= fb;
        fa--;
      }
      else
      {
        fb--;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
