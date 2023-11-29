# include <stdio.h>

int contaNum(int k, int n)
{
  int qtd = 0;
  if(n > 0)
  {
      qtd = contaNum(k, n / 10);
      if(k == n % 10)
      {
        qtd ++;
      }
  }
  return qtd;
}



int main()
{
  printf("%d\n", contaNum(1, 111));
}
