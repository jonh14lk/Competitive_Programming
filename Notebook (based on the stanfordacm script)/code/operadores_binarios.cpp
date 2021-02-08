#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pd pair<double, int>
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 200001
#define mod 1000000007

void shifts ()
{
  bitset <4> bs;
  bs.reset();
  bs[2] = true;
  bs[3] = true; 
  cout << bs << endl ; // 1100
  bs >>= 1; // 0110
  bs <<= 1; // 1100
  bs >>= 2; // 0011
  bs <<= 2; // 1100
  bs >>= 3; // 0001
  bs <<= 3; // 1000
  cout << bs << endl ;
}
void op_xor ()
{
  // 0 ^ 0 = 0
  // 0 ^ 1 = 1
  // 1 ^ 0 = 1
  // 1 ^ 1 = 0
  bitset <4> bs , bs2;
  bs.reset(); 
  bs2.reset();
  bs[2] = true;
  bs[3] = true; 
  bs2[1] = true;
  bs2[3] = true;
  bs ^= bs2; // bs = bs ^ bs2
  cout << bs.count() << endl ; 
}
void op_and ()
{
  // 0 & 0 = 0
  // 0 & 1 = 0
  // 1 & 0 = 0
  // 1 & 1 = 1
  bitset <4> bs , bs2;
  bs.reset(); 
  bs2.reset();
  bs[2] = true;
  bs[3] = true; 
  bs2[1] = true;
  bs2[3] = true;
  bs &= bs2; // bs = bs & bs2
  cout << bs.count() << endl ; 
}
void op_or ()
{
  // 0 | 0 = 0
  // 0 | 1 = 1
  // 1 | 0 = 1
  // 1 | 1 = 1
  bitset <4> bs , bs2;
  bs.reset(); // poe tudo 0 
  bs2.reset();
  bs[2] = true;
  bs[3] = true; 
  bs2[1] = true;
  bs2[3] = true;
  bs |= bs2; // bs = bs | bs2
  cout << bs.count() << endl ; // quantidade de 1
}
signed main()
{
  op_or();
  op_and();
  op_xor();
  shifts();
  return 0;
}
