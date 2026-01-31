#include <stdio.h>
#include "L05-Project.h"

int main()
{
    int num;
    printf("Enter a positive number: ");
    scanf("%i", &num);

    print_factors(num, 1);

    return 0;

}

void print_factors(int num, int i) // Needed to define an int i as an iterator since recursive
{
    if (i > num)
    {
        return;
    }

    else if (num % i == 0 && num != i)
    {
        printf("%d ", i);
    }
    
    // no return function here because its recursive
    print_factors(num, ++i);
}