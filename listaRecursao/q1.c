# include <stdio.h>

int calcFat(int num)
{
    if(num == 0 || num == 1)
    {
        return 1;
    }
    else 
    {
        return num * (calcFat(num - 1));
    }
}


int main()
{
    printf("%d\n", calcFat(5));

}