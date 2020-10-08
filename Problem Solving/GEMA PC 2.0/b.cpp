#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define pb push_back

lli v[100001];
lli seg_tree[400004];

void update(lli i, lli l, lli r, lli pos, lli x)
{
  if (l == r)
  {
    seg_tree[i] = x;
  }
  else
  {
    lli mid = (l + r) / 2;

    if (pos <= mid)
    {
      update(2 * i, l, mid, pos, x);
    }
    else
    {
      update((2 * i) + 1, mid + 1, r, pos, x);
    }

    seg_tree[i] = seg_tree[2 * i] + seg_tree[(2 * i) + 1];
  }
}
lli query(lli i, lli l, lli r, lli ql, lli qr)
{
  if (l >= ql && r <= qr)
  {
    return seg_tree[i];
  }

  if (l > qr || r < ql)
  {
    return 0;
  }

  lli mid = (l + r) / 2;

  return query(2 * i, l, mid, ql, qr) + query((2 * i) + 1, mid + 1, r, ql, qr);
}
void build(lli l, lli r, lli i)
{
  if (l == r)
  {
    seg_tree[i] = v[l];
    return;
  }

  lli mid = (l + r) / 2;

  build(l, mid, 2 * i);
  build(mid + 1, r, (2 * i) + 1);

  seg_tree[i] = seg_tree[2 * i] + seg_tree[(2 * i) + 1];
}
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  lli n, ql, qr, aux, m, ans;

  cin >> n;

  for (lli i = 0; i < n; i++)
  {
    cin >> v[i];
  }

  int q;
  cin >> q;

  build(0, n - 1, 1);

  while (q--)
  {
    lli a, b;
    cin >> a >> b;

    lli c = a - 1;
    a--;
    b--;

    lli mid, start = a, end = n - 1, ans = -1, ans2 = -1;
    while (start <= end)
    {
      mid = (start + end) / 2;
      lli at = query(1, 0, n - 1, a, mid);
      if (at == b)
      {
        ans = mid;
        start = mid + 1;
        break;
      }
      else if (at < b)
      {
        start = mid + 1;
        ans2 = mid;
      }
      else
      {
        end = mid - 1;
      }
    }

    if (ans == -1)
    {
      (ans2 == -1) ? cout << -1 << endl : cout << ans2 + 1 << endl;
    }
    else
    {
      cout << ans + 1 << endl;
    }
  }

  return 0;
}