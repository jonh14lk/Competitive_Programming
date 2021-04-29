// functions to print and read a __int128 in c++
__int128 read()
{
  __int128 x = 0, f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9')
  {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9')
  {
    x = x * 10 + ch - '0';
    ch = getchar();
  }
  return x * f;
}
void print(__int128 x)
{
  if (x < 0)
  {
    cout << "-";
    x = -x;
  }
  if (x > 9)
    print(x / 10);
  char at = (x % 10) + '0';
  cout << at;
}
