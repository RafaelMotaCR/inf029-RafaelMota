# include <stdio.h>
# include <stdlib.h>


void printaNumAZero(int target)
{
  if(target >= 0){
    printf(" %d ", target);
    printaNumAZero(target - 1);
  }
}


void printaZeroANum(int target)
{
  if (target >= 0)
  {
    printaZeroANum(target - 1);
    printf(" %d ", target);
  }
}


int somaNum(int target)
{
  int soma = 0;
  if(target >= 1)
  {
    somaNum(target - 1);
    soma += target;
  }
  return soma;
}


int somaNum(int target)
{
  if(target >= 1)
  {
    return target + somaNum(target - 1);
  }
}


int main(){
       printf("\n%d\n", somaNum(2));
  

    return 0;
}