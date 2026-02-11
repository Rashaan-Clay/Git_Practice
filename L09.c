#include <stdio.h>

/**
 *  Creates int variables for width, length, and area of a room
    Creates int* pointers to the width, length, and area variables
    Prompts users to enter the width and length of a room, using the pointers when storing input
    Use one or more calls to the scanf function to gather input
    Calculates the area (width × length) of the room, using the pointers for accessing the width, length, and area values
    Prints the width, length, and area, using pointers to the values
    Use a single call to the printf function for printing the results
 */

int main()
{
    int width, length, area; // Initialize some varaibles
    int* Pw = &width; 
    int* Pl = &length; // Intiliaze pointers to the addresses of those variables
    int* Pa = &area;

    printf("Enter the width of the room: ");
    scanf("%d", Pw); // you have now stored these values in memory and you can view them just as simple as passing-by-value

    printf("Enter the lenghth of the room: ");
    scanf("%d", Pl);

    *Pa = *Pl * *Pl; // Dereference your pointers and multiply the pointer-at values to together and store it.

    printf("area: %d\nlength: %d\nwidth: %d", *Pa, *Pl, *Pw); // correct placeholder for pointers is %d

    return 0;
}