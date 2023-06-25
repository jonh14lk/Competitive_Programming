#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n;
  cin >> n;
  set<int> s;
  for (int i = 0; i < n; i++)
  {
    int year, age;
    cin >> year >> age;
    s.insert(year - age);
  }
  (s.size() == 1) ? cout << "idades corretas\n" : cout << "mentiu a idade\n";
}