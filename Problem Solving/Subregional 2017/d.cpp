#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 5001
#define mod 1000000007

vector<int> facts;

void primefactors(int n)
{
  while (n % 2 == 0)
  {
    facts.pb(2);
    n = n / 2;
  }
  for (int i = 3; i <= sqrt(n); i += 2)
  {
    while (n % i == 0)
    {
      facts.pb(i);
      n = n / i;
    }
  }
  if (n > 2)
    facts.pb(n);
}
bool is(int n)
{
  facts.clear();
  primefactors(n);
  set<int> s;
  for (auto const &i : facts)
    s.insert(i);
  return (s.size() == facts.size() && facts.size() >= 2);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  int ans = 0;
  for (int i = 1; i <= sqrt(n); i++)
  {
    if (!(n % i))
    {
      if (is(i))
        ans++;
      if (n / i != i)
        if (is(n / i))
          ans++;
    }
  }
  cout << ans << endl;
}