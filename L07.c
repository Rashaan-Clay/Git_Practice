#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
    Prompts the user to enter text
    You must display a message with instructions
    Use the fgets function to read-in the user input
    Converts the input entirely to uppercase letters
    Prints the resulting string
*/

int main(void)
{
    char input[100];
    fgets(input, 100, stdin);
    size_t n = strnlen(input, 100); // size_t and int works here. size_t is only positive integers.

    for (int i = 0; i < n; i++)
    {
        input[i] = toupper(input[i]);
    }

    printf("%s", input);

    return 0;
}