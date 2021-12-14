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

int kk, n;
int v[MAXN];
int mp[MAXN];
int mp2[MAXN];
int with[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> kk >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    mp[v[i]]++;
  }
  if (n == 1)
  {
    cout << "-" << v[0] << endl;
    return 0;
  }
  set<int> s;
  for (int i = 1; i <= kk; i++)
  {
    s.insert(mp[i]);
    with[mp[i]] = i;
    mp2[mp[i]]++;
  }
  if (s.size() == 2)
  {
    bool can = 0;
    for (auto const &i : s)
    {
      for (auto const &j : s)
      {
        if (i != j)
        {
          if (mp2[i] == 1 && mp2[j] == kk - 1 && i + 1 == j && !can)
          {
            cout << "+" << with[i] << endl;
            can = 1;
          }
          else if (mp2[i] == 1 && mp2[j] == kk - 1 && i - 1 == j && !can)
          {
            cout << "-" << with[i] << endl;
            can = 1;
          }
        }
      }
    }
    if (!can)
      cout << "*\n";
  }
  else if (s.size() == 3)
  {
    bool can = 0;
    for (auto const &i : s)
    {
      for (auto const &j : s)
      {
        for (auto const &k : s)
        {
          if (i != j && i != k && j != k)
          {
            if (mp2[i] == 1 && mp2[j] == 1 && mp2[k] == kk - 2 && i + 1 == k && j - 1 == k && !can)
            {
              cout << "-" << with[j] << " +" << with[i] << endl;
              can = 1;
            }
          }
        }
      }
    }
    if (!can)
      cout << "*\n";
  }
  else
  {
    cout << "*\n";
  }
  return 0;
}
