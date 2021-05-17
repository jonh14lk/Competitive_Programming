#include <bits/stdc++.h>
#define DEBUG if (0)
#define lli long long int
#define ldouble long double
using namespace std;

const double eps = 1e-9;

lli kadane(vector<lli> &a)
{
  int n = a.size();
  lli max_so_far = 0, max_ending_here = 0;
  lli i;
  for (i = 0; i < n; i++)
  {
    max_ending_here = max_ending_here + a[i];

    if (max_so_far < max_ending_here)
      max_so_far = max_ending_here;
    if (max_ending_here < 0)
      max_ending_here = 0;
  }
  return max_so_far;
}

lli maxCircularSum(vector<lli> &a)
{
  int n = a.size();
  // Case 1: get the maximum sum using standard kadane'
  // s algorithm
  lli max_kadane = kadane(a);
  // if maximum sum using standard kadane' is less than 0
  if (max_kadane < 0)
    return max_kadane;

  // Case 2: Now find the maximum sum that includes
  // corner elements.
  lli max_wrap = 0, i;
  for (i = 0; i < n; i++)
  {
    max_wrap += a[i]; // Calculate array-sum
    a[i] = -a[i];     // invert the array (change sign)
  }

  // max sum with corner elements will be:
  // array-sum - (-max subarray sum of inverted array)
  max_wrap = max_wrap + kadane(a);

  // The maximum circular sum will be maximum of two sums
  return (max_wrap > max_kadane) ? max_wrap : max_kadane;
}

const int maxN = 1e5;
int n;
struct Point
{
  lli x, y, a, s, value, lolvalue;
  ldouble angle;
  int idx;
  void read()
  {
    scanf("%lld %lld %lld %lld", &x, &y, &a, &s);
    value = a - s;
    lolvalue = s - a;
    angle = atan2l(y, x);
  }
  bool operator<(const Point &other) const
  {
    return angle < other.angle;
  }
  bool sameLine(const Point &other)
  {
    // return abs(angle - other.angle) <= eps;
    // if (x == other.x) return true;
    // if (y == other.y) return true;
    return y * other.x == other.y * x;
  }
};
vector<Point> points;

int main()
{
  while (~scanf("%d", &n))
  {
    points.clear();
    points.resize(n);
    for (int i = 0; i < n; i++)
    {
      points[i].read();
      points[i].idx = i;
    }
    sort(points.begin(), points.end());

    // assert(!points[0].sameLine(points[n - 1]));

    int start = n - 1;
    while (start - 1 >= 0 && points[start].sameLine(points[start - 1]))
      start--;

    vector<Point> aux = points;
    for (int i = 0; i < n; i++)
      points[i] = aux[(start + i) % n];

    vector<lli> values;
    for (int i = 0; i < n; i++)
    {
      int j = i;
      lli total = points[i].value;
      while (j + 1 < n && points[i].sameLine(points[j + 1]))
      {
        j++;
        total += points[j].value;
      }

      values.push_back(total);
      i = j;
    }
    lli ans = maxCircularSum(values);

    printf("%lld\n", ans);
  }
  return 0;
}