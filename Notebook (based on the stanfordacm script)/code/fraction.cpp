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
#define MAXN 200006
#define mod 1000000007

struct fraction
{
  int x, y; // x / y

  fraction() {}
  fraction(int x, int y) : x(x), y(y) {}
  bool operator==(fraction o) { return (x * o.y == o.x * y); }
  bool operator!=(fraction o) { return (x * o.y != o.x * y); }
  bool operator>(fraction o) { return (x * o.y > o.x * y); }
  bool operator>=(fraction o) { return (x * o.y >= o.x * y); }
  bool operator<(fraction o) { return (x * o.y < o.x * y); }
  bool operator<=(fraction o) { return (x * o.y <= o.x * y); }
  fraction operator+(fraction o)
  {
    fraction ans;
    ans.y = (y == o.y) ? y : y * o.y;
    ans.x = (x) * (ans.y / y) + (o.x) * (ans.y / o.y);
    // ans.simplify();
    return ans;
  }
  fraction operator*(fraction o)
  {
    fraction ans;
    ans.x = x * o.x;
    ans.y = y * o.y;
    // ans.simplify();
    return ans;
  }
  fraction inv()
  {
    fraction ans = fraction(x, y);
    swap(ans.x, ans.y);
    return ans;
  }
  fraction neg()
  {
    fraction ans = fraction(x, y);
    ans.x *= -1;
    return ans;
  }
  void simplify()
  {
    if (abs(x) > 1e9 || abs(y) > 1e9) // slow simplification
    {
      int g = __gcd(y, x);
      x /= g;
      y /= g;
    }
  }
  // substraction and division can be easily done
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}