#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define mod 1000000007

bool check(int n, int b)
{
    vector<int> v;
    while (n > 0)
    {
        v.push_back(n % b);
        n /= b;
    }
    vector<int> v2 = v;
    reverse(v.begin(), v.end());
    return (v == v2);
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    set<int> s;
    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            s.insert(i);
            s.insert(n / i);
        }
    }
    set<int> ans;
    for (auto const &i : s)
    {
        if (i >= 3 && check(n, i - 1))
            ans.insert(i - 1);
    }
    for (int i = 2; i <= min(n, 1000005ll); i++)
    {
        if (check(n, i))
            ans.insert(i);
    }
    if (!ans.size())
        cout << "*";
    for (auto const &i : ans)
        cout << i << " ";
    cout << endl;
}