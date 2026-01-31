#include <stdio.h>
#include "L05-Project.h"

int main()
{
    int value;
    printf("Enter a positive number: ");
    scanf("%i", &value);

    print_factors(value, value);

    return 0;

}

void print_factors(int num, int i)  // (4)
{
    if (i <= 0)
    {
        return;
    }
    else if (num % i == 0 && num != i) // 4 mod 4 == 0, 4 mod 3, 4 mod 2 == 0
    {
        printf("%d ", i);
    }

    print_factors(num, i - 1);
}