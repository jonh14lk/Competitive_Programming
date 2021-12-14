#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007

vector<char> vog = {'a', 'e', 'i', 'o', 'u'};

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  deque<char> t = {s.begin(), s.end()};
  auto imp = [&]()
  {
    cout << 0 << endl;
    exit(0);
  };
  auto is = [&](char c)
  {
    return binary_search(vog.begin(), vog.end(), c);
  };
  auto apaga = [&](bool fim)
  {
    (fim) ? t.pop_back() : t.pop_front();
  };
  int num = 0;
  for (auto const &i : t)
  {
    num += is(i);
  }
  int ans = 1;
  bool is_rev = false;
  while (t.size())
  {
    char l = t.front(), r = t.back();
    if (is_rev)
    {
      swap(l, r);
    }
    if (!is(l) && !is(r))
    {
      apaga(1 ^ is_rev);
    }
    else if (is(l) && is(r))
    {
      apaga(0 ^ is_rev);
      num--;
      is_rev ^= 1;
    }
    else if (!is(l) && is(r))
    {
      imp();
    }
    else
    {
      if (num == 1)
        ans++;
      apaga(1 ^ is_rev);
    }
  }
  cout << ans << endl;
  return 0;
}