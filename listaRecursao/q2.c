# include <stdio.h>

int fib(int n, int fibn)
{
   // return fib(n,); 
}

int main()
{
    int n1 = 0, n2 =1, n3;
    int n = 10;
    for(int i = 0; i < n; i++)
    {
        if(i == 0)
        {
            printf(" 0 ");
            continue;
        }
        printf(" %d ", n1 + n2);
        n3 = n1;
        n1 = n2;
        n2 = n2 + n3;
    }

}