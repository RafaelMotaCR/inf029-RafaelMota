# include <stdio.h>

int somaRecursiva(int n) {
    if (n <= 0)
        return 0;
    else
        return n + somaRecursiva(n - 1);
}


int main()
{
    printf("%d\n", somaAteNum(9));
    return 0;

}
