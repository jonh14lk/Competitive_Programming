#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 10005
#define mod 998244353

const int inf = 1e18;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, l;
  cin >> n >> l;
  vector<pi> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i].fir, v[i].fir--;
  for (int i = 0; i < n; i++)
    cin >> v[i].sec, v[i].sec--;
  auto solve_different_directions = [&](pi a, pi b, bool clock, bool clock2) -> bool
  {
    vector<pi> intera, interb;
    if (a.fir <= a.sec)
    {
      if (clock)
        intera.pb({a.fir, a.sec});
      else
        intera.pb({0, a.fir}), intera.pb({a.sec, l - 1});
    }
    else
    {
      if (!clock)
        intera.pb({a.sec, a.fir});
      else
        intera.pb({a.fir, l - 1}), intera.pb({0, a.sec});
    }
    if (b.fir <= b.sec)
    {
      if (clock2)
        interb.pb({b.fir, b.sec});
      else
        interb.pb({0, b.fir}), interb.pb({b.sec, l - 1});
    }
    else
    {
      if (!clock2)
        interb.pb({b.sec, b.fir});
      else
        interb.pb({b.fir, l - 1}), interb.pb({0, b.sec});
    }
    for (auto [l1, r1] : intera)
    {
      for (auto [l2, r2] : interb)
      {
        if (l1 >= l2 && l1 <= r2)
          return 0;
        if (l2 >= l1 && l2 <= r1)
          return 0;
      }
    }
    return 1;
  };
  auto solve_equal_directions = [&](pi a, pi b, bool clock) -> bool
  {
    int da = (a.sec - a.fir + l) % l;
    int db = (b.sec - b.fir + l) % l;
    if (!clock)
    {
      da = l - da;
      db = l - db;
    }
    if (da < db)
    {
      swap(a, b);
      swap(da, db);
    }
    int dist = (b.sec - a.fir + l) % l;
    if (!clock)
      dist = l - dist;
    return !(dist >= db && dist <= da);
  };
  auto check = [&](pi a, pi b, bool clock, bool clock2) -> bool
  {
    if (clock != clock2)
      return solve_different_directions(a, b, clock, clock2); // check if has intersection
    return solve_equal_directions(a, b, clock);               // check if has overtaking
  };
  auto calc_dist = [&](int i, bool is_clockwise)
  {
    int dclock = (v[i].sec - v[i].fir + l) % l;
    if (!is_clockwise)
      return l - dclock;
    return dclock;
  };
  auto solve = [&](bool clock0)
  {
    int mx = calc_dist(0, clock0);
    if (n == 1)
      return mx;
    vector<bool> dir(n);
    dir[0] = clock0;
    for (int i = 1; i < n; i++) // find other directions knowing that we fixed the direction of the first guy
    {
      int valid_dir = -1;
      for (int curr_dir = 0; curr_dir < 2; curr_dir++)
      {
        if (check(v[0], v[i], dir[0], curr_dir))
        {
          valid_dir = curr_dir;
          break;
        }
      }
      if (valid_dir == -1)
        return inf;
      mx = max(mx, calc_dist(i, valid_dir));
      dir[i] = valid_dir;
    }
    // it is possible to check this in O(n)
    // just look to the pairs i and (i + 1) % n (when sorted)
    // but since n <= 1000, this isnt necessary
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 1; j < n; j++)
        if (!check(v[i], v[j], dir[i], dir[j])) // check if all pairs does not intersect
          return inf;
    }
    return mx;
  };
  int ans = min(solve(0), solve(1));
  (ans >= inf) ? cout << "*\n" : cout << ans << endl;
  return 0;
}