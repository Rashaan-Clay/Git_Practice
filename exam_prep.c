#include <stdio.h>

struct address
{
    int nums;
    int gallons;
};

int main()
{
    struct address bottle;
   
    int nums = bottle.gallons = 12;


    printf("%d",nums);
    return 0;
}