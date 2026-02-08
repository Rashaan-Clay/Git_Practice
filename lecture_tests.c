#include <stdio.h>

int main(void)
{
    int arr[] = {1,2,3,4,5,51,12,123,123,1321,3123,123,112312,};

    printf("%d", sizeof(arr) / sizeof(arr[0]));

}