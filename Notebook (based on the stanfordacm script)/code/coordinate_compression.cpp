#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500005
#define mod 1000000007

void compress(vector<int> &v)
{
  vector<int> val;
  for (auto const &i : v)
    val.pb(i);
  sort(val.begin(), val.end());
  val.erase(unique(val.begin(), val.end()), val.end());
  for (auto &i : v)
    i = lower_bound(val.begin(), val.end(), i) - val.begin();
}