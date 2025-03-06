// achar valor maximo da funcao
for (int i = 0; i < 400; i++)
{
  double m1 = l + (r - l) / 3;
  double m2 = r - (r - l) / 3;
  double f1 = f(m1);
  double f2 = f(m2);
  if (f1 < f2)
    l = m1;
  else
    r = m2;
}