 #include <stdio.h>
 #include <string.h>
 #include <errno.h>
 #include <stdlib.h>


/**
 *  Write a C program that dynamically allocates memory for an array, populates the array, and then prints its contents.

        Your program must implement the functions shown below:

        Function: create_array
            Tasks:
                * Creates an array of integers using malloc
                    * Display an error message and exit the program if the array cannot be allocated

                * Populate each element with a value in the range [1, 100]
                    * Account for the size of the array specified when calling create_array
                
                * Returns the created array
                     
            Parameter:
                * size_t with the number of elements to be present in the created array
        
            Other input: None
            Returns: int*
*/
int* create_array(size_t n)
{
    int* array = (int*) malloc(n * sizeof(int)); // Returning a pointer at a data strcuture and returned with malloc function. Rather than hard-coding a number of bytes, you pass in a specified size and multiply it by the size of the data type (int)
    
    if (array == NULL) // If array is a null pointer or does not point to anything
    {
        printf("Failed: %s.\n",strerror(errno));
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        int value = rand();
        array[i] = value * (rand() % (100 + 1)); // Range between 1 - 100
                                                // 100 being the upper-bound
    }
    return array;

    free(array);
    array = NULL;
}

/*
        Function: print_array
            Tasks:
                * Print the contents of the passed-in array, one number per row
            
            Parameters:
                * int* for the array to be printed
                * size_t for the number of items in the array
        
            Other input: None
            Returns: void
*/
void print_array(int* array, size_t n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", array[i]);
    }
    
    return;
}

/*
        Function: main
            Tasks:
                * Calls the create_array function to create an array with 5 integers
                * Passes the created array to the print_array function to be printed
        
            Parameters: None
            Other input: None
            Returns: int

*/
int main()
{
    int* arr = create_array(5);// Call the function to create the array and store the returned pointer
    print_array(arr, 5);

    return 0;
}