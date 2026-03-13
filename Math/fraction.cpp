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
  fraction(int _x) : x(_x), y(1) { this->normalize(); }
  fraction(int _x, int _y) : x(_x), y(_y) { this->normalize(); }
  const bool operator==(const fraction o) const { return ((__int128)x * o.y == (__int128)o.x * y); }
  const bool operator!=(const fraction o) const { return ((__int128)x * o.y != (__int128)o.x * y); }
  const bool operator>(const fraction o) const { return ((__int128)x * o.y > (__int128)o.x * y); }
  const bool operator>=(const fraction o) const { return ((__int128)x * o.y >= (__int128)o.x * y); }
  const bool operator<(const fraction o) const { return ((__int128)x * o.y < (__int128)o.x * y); }
  const bool operator<=(const fraction o) const { return ((__int128)x * o.y <= (__int128)o.x * y); }
  fraction operator+(fraction o)
  {
    fraction ans;
    ans.y = (y == o.y) ? y : y * o.y;
    ans.x = (x) * (ans.y / y) + (o.x) * (ans.y / o.y);
    ans.normalize();
    return ans;
  }
  fraction operator*(fraction o)
  {
    fraction ans;
    ans.x = x * o.x;
    ans.y = y * o.y;
    ans.normalize();
    return ans;
  }
  fraction inv()
  {
    fraction ans = fraction(x, y);
    swap(ans.x, ans.y);
    ans.normalize();
    return ans;
  }
  fraction neg()
  {
    fraction ans = fraction(x, y);
    ans.x *= -1;
    ans.normalize();
    return ans;
  }
  fraction operator-(fraction o)
  {
    return *this + o.neg();
  }
  fraction operator/(fraction o)
  {
    return *this * o.inv();
  }
  void normalize()
  {
    if (y < 0)
    {
      y *= -1;
      x *= -1;
    }
    int g = __gcd(abs(y), abs(x));
    x /= g;
    y /= g;
  }
  double val()
  {
    return (double)x / y;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}