/**
 * @file CharPointerSolution.c
 * @brief Participation Project L08 solution using char*[] strings
 * @author Brian Powell
 */

// Include header files
#include <stdio.h>
#include <string.h>
#include <stddef.h>

// Function prototypes
void bubble_sort(char* sort_array[], size_t sort_array_size);

/**
 * @brief Program entry point
 * @return Status code
*/
int main(void)
{
	// Define foods array
	char* foods[5] = { "tacos", "pizza", "lasagna", "steak", "shrimp" };

	// Call bubble sort
	bubble_sort(foods, sizeof(foods) / sizeof(foods[0]));

	// Print results
	for (size_t i = 0; i < sizeof(foods) / sizeof(foods[0]); i++)
	{
		printf("%s\n", foods[i]);
	}

	return 0;
}

/**
 * Uses bubble sort to sort an array of strings
 * @param sort_array Array to sort
 * @param sort_array_size Number of strings in the array
*/
void bubble_sort(char* sort_array[], size_t sort_array_size)
{
	// Setup outer loop for passes
	for (size_t i = 0; i < sort_array_size - 1; i++)
	{
		// Check pairs of elements
		for (size_t j = 0; j < sort_array_size - 1 - i; j++)
		{
			// Compare values for potential swapping
			if (strcmp(sort_array[j], sort_array[j + 1]) > 0)
			{
				// Swap positions
				char* temp = sort_array[j];
				sort_array[j] = sort_array[j + 1];
				sort_array[j + 1] = temp;
			}
		}
	}

}