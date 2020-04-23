#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define pd <double, double> 
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

struct pt
{
  double x , y;
  pt operator + (pt p) {return {x + p.x , y + p.y};} // soma de pontos
  pt operator - (pt p) {return {x - p.x , y - p.y};} // subtração de pontos
  pt operator * (double d) {return {x * d , y * d};} // multiplicação por um double
  pt operator / (double d) {return {x / d , y / d};} // divisão por um double
};
double dot(pt v, pt w) // produto escalar (dot product)
{
  return v.x * w.x + v.y * w.y;
}
bool isPerp(pt v, pt w) // retorna se dois vetores sao perpendiculares (angulo 90 graus)
{
  return dot(v , w) == 0;
}
double cross(pt v, pt w) // produto vetorial (cross product)
{
  return v.x * w.y - v.y * w.x;
}
double orient(pt a, pt b, pt c) // se for = 0 os vetores são colineares
{
  return cross(b - a , c - a);
}
double dist(pt a, pt b) // distancia entre 2 pontos
{
  pt c = a - b;
  return sqrt(c.x * c.x + c.y * c.y);
}
double ccw(pt a, pt b, pt c) // retorna se forma um angulo convexo ou concavo
{
  double ret = cross(b - a, c - b);
  return ret < 0;
}
signed main()
{
  return 0;
}
