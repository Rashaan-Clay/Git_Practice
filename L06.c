#include <stdio.h>
void bubble_sort(int nums[], int n);

int main()
{
    int nums[] = {1,2,3,4,5,6,7,8,9,10};
    int size = sizeof(nums) / sizeof(nums[0]);

    bubble_sort(nums, size);
    for (int i = 0; i < size; i++)
    {
        printf("%d", nums[i]);
    }
    printf("\n");
}


void bubble_sort(int nums[], int n)
{
    
    for (int i = 0; i < n; i++)
    {
        for (int j =0; j < n-i-1; j++) // because we started at i = 0; we subtract the total size from the the already-sorted elements (n-i)
                                       // You subtract 1 from the entire condition to offset we'll be swapping with an element greater 1 beyond our current position
                                       // so you dont go out of bounds (n-i-1); -1 is to stop one position early
        {
            if (nums[j] > nums[j+1]) 
            {
                int temp = nums[j];
                nums[j] = nums[j+1];
                nums[j+1] = temp;
            }
        }
    }
}