#include <bits/stdc++.h>

using namespace std;
#define int long long int
#define fir first
#define sec second
#define pb push_back
#define mod 1000000009
#define pi pair<int, int>
#define MAXN 100005

int n, k, l, sum, sum2;
int a[MAXN];
int b[MAXN];
multiset<int> s1, s2;

void rem(int i)
{
    sum -= a[i];
    if (s1.find(b[i]) != s1.end())
    {
        s1.erase(s1.find(b[i]));
        sum2 -= b[i];
        if (s2.size() > 0)
        {
            int aux = *s2.rbegin();
            s2.erase(s2.find(aux));
            s1.insert(aux);
            sum2 += aux;
        }
    }
    else 
    {
        s2.erase(s2.find(b[i]));
    }
}
void add(int i)
{
    sum += a[i];
    if (s1.size() < l)
    {
        s1.insert(b[i]);
        sum2 += b[i];
    }
    else if (b[i] > (*s1.begin()))
    {
        int aux = *s1.begin();
        s1.erase(s1.find(aux));
        sum2 -= aux;
        s2.insert(aux);
        s1.insert(b[i]);
        sum2 += b[i];
    }
    else 
    {
        s2.insert(b[i]);
    }
}
int solve()
{
    return sum + sum2;
}
signed main() 
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];
    cin >> k >> l;
    for (int i = 0; i < k; i++)
    {     
        add(i);
    }
    int ans = solve();
    int l = k - 1, r = n - 1;
    while(l >= 0)
    {
        rem(l);
        add(r);
        ans = max(ans, solve());
        l--, r--;
    }
    cout << ans << endl;
}