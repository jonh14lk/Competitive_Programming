#include <bits/stdc++.h>
using namespace std;
 
#define lli long long int
#define pb push_back
#define in insert
#define pi pair<int, int>
#define point pair<double, double> // ponto
#define line pair<point,point> // linha
#define pii pair<int, pi>
#define mp make_pair
#define fir first
#define sec second
#define MAXN 100001
#define mod 1000000007

double prod_escalar(point a, point b) // calculo do produto escalar (dot product)
{
  return a.fir * b.fir + a.sec * b.sec;
}
double prod_vetorial(point a, point b) // calculo do produto vetorial(cross product)
{
  return a.fir * b.sec - a.sec * b.fir;
}
point sum(point a, point b) // ponto a + ponto b
{
  point ret;
  ret.fir = a.fir + b.fir;
  ret.sec = a.sec + b.sec;
  return ret;
}
point sub(point a, point b) // ponto a - ponto b
{
  point ret;
  ret.fir = a.fir - b.fir;
  ret.sec = a.sec - b.sec;
  return ret;
}
point neg(point a) // inverter o sinal das cordenadas de um ponto
{
  point ret;
  ret.fir = -a.fir;
  ret.sec = -a.sec;
  return ret;
}
double dist(point a, point b) // distancia entre 2 pontos
{
  point c = sub(a , b);
  return sqrt(c.fir * c.fir + c.sec * c.sec);
}
double area(vector <point> p) // area de um poligono definido por um vector ordenado de pontos
{
  double ret = 0;
  for(int i = 2; i < p.size(); i++)
    ret += prod_vetorial(sub(p[i] , p[0]), sub(p[i - 1] , p[0])) / 2;
  return abs(ret);
}
double ccw(point a, point b, point c) // retorna se forma um angulo convexo ou concavo
{
  double ret = prod_vetorial(sub(b , a), sub(c , b));
  return ret < 0;
}
signed main()
{
  return 0;
}
